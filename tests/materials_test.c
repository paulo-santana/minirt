#include "lights/lights.h"
#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
#include "tuple/tuple.h"
#include <math.h>

MunitResult material_test1(const MunitParameter params[], void *fixture)
{
	t_material *m = new_material();

	munit_assert_float(m->color->red , ==, 1);
	munit_assert_float(m->color->green , ==, 1);
	munit_assert_float(m->color->blue , ==, 1);
	munit_assert_float(m->ambient, ==, 0.1);
	munit_assert_float(m->diffuse, ==, 0.9);
	munit_assert_float(m->specular, ==, 0.9);
	munit_assert_float(m->shininess, ==, 200.0);
	return (MUNIT_OK);
}

// lighting with the eye between the light and the surface
MunitResult material_test2(const MunitParameter params[], void *fixture)
{
	t_material *m = new_material();
	t_tuple *position = new_point(0, 0, 0);

	t_tuple *eyev = new_vector(0, 0, -1);
	t_tuple *normalv = new_vector(0, 0, -1);
	t_point_light *light = new_point_light(new_point(0, 0, -10), new_color(1, 1, 1));
	t_lighting_args args;

	args.material = m;
	args.light = light;
	args.position = position;
	args.eye_vector = eyev;
	args.normal_vector = normalv;

	t_color *result = lighting(&args);

	munit_assert_true(fequals(result->red, 1.9));
	munit_assert_true(fequals(result->green, 1.9));
	munit_assert_true(fequals(result->blue, 1.9));

	free(m->color);
	free(m);
	return (MUNIT_OK);
}

// lighting with the eye offset 45º
MunitResult material_test3(const MunitParameter params[], void *fixture)
{
	t_material *m = new_material();
	t_tuple *position = new_point(0, 0, 0);

	t_tuple *eyev = new_vector(0, M_SQRT2 / 2, -M_SQRT2 / 2);
	t_tuple *normalv = new_vector(0, 0, -1);
	t_point_light *light = new_point_light(new_point(0, 0, -10), new_color(1, 1, 1));
	t_lighting_args args;

	args.material = m;
	args.light = light;
	args.position = position;
	args.eye_vector = eyev;
	args.normal_vector = normalv;

	t_color *result = lighting(&args);

	munit_assert_true(fequals(result->red, 1.0));
	munit_assert_true(fequals(result->green, 1.0));
	munit_assert_true(fequals(result->blue, 1.0));

	free(m->color);
	free(m);
	return (MUNIT_OK);
}

// lighting with the light offset 45º
MunitResult material_test4(const MunitParameter params[], void *fixture)
{
	t_material *m = new_material();
	t_tuple *position = new_point(0, 0, 0);

	t_tuple *eyev = new_vector(0, 0, -1);
	t_tuple *normalv = new_vector(0, 0, -1);
	t_point_light *light = new_point_light(new_point(0, 10, -10), new_color(1, 1, 1));
	t_lighting_args args;

	args.material = m;
	args.light = light;
	args.position = position;
	args.eye_vector = eyev;
	args.normal_vector = normalv;

	t_color *result = lighting(&args);

	munit_assert_true(fequals(result->red, 0.7364));
	munit_assert_true(fequals(result->green, 0.7364));
	munit_assert_true(fequals(result->blue, 0.7364));

	free(m->color);
	free(m);
	return (MUNIT_OK);
}

// lighting with the eye in the path of the reflection vector
MunitResult material_test5(const MunitParameter params[], void *fixture)
{
	t_material *m = new_material();
	t_tuple *position = new_point(0, 0, 0);

	t_tuple *eyev = new_vector(0, -M_SQRT2/2, -M_SQRT2/2);
	t_tuple *normalv = new_vector(0, 0, -1);
	t_point_light *light = new_point_light(new_point(0, 10, -10), new_color(1, 1, 1));
	t_lighting_args args;

	args.material = m;
	args.light = light;
	args.position = position;
	args.eye_vector = eyev;
	args.normal_vector = normalv;

	t_color *result = lighting(&args);

	munit_assert_true(fequals(result->red, 1.63638));
	munit_assert_true(fequals(result->green, 1.63638));
	munit_assert_true(fequals(result->blue, 1.63638));

	free(m->color);
	free(m);
	return (MUNIT_OK);
}

// lighting with the eye in the path of the reflection vector
MunitResult material_test6(const MunitParameter params[], void *fixture)
{
	t_material *m = new_material();
	t_tuple *position = new_point(0, 0, 0);

	t_tuple *eyev = new_vector(0, 0, -1);
	t_tuple *normalv = new_vector(0, 0, -1);
	t_point_light *light = new_point_light(new_point(0, 0, 10), new_color(1, 1, 1));
	t_lighting_args args;

	args.material = m;
	args.light = light;
	args.position = position;
	args.eye_vector = eyev;
	args.normal_vector = normalv;

	t_color *result = lighting(&args);

	munit_assert_true(fequals(result->red, 0.1));
	munit_assert_true(fequals(result->green, 0.1));
	munit_assert_true(fequals(result->blue, 0.1));

	free(m->color);
	free(m);
	return (MUNIT_OK);
}
