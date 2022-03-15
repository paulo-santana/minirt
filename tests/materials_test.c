#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
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
