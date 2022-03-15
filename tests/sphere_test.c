#include "matrix/matrix.h"
#include "munit/munit.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "ray/ray.h"
#include <stdlib.h>

MunitResult sphere_test1(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_matrix *identity = identity_matrix();

	munit_assert_true(matrix_equals(sphere->transform, identity));
	free(identity);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}

MunitResult sphere_test2(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_ray *ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_matrix *t = translation(2, 3, 4);

	set_transform(sphere, t);
	munit_assert_ptr_equal(sphere->transform, t);
	destroy_sphere(sphere);
	destroy_ray(ray);
	return (MUNIT_OK);
}

MunitResult sphere_test3(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_ray *ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_matrix *s = scaling(2, 2, 2);
	t_intersections *xs;

	set_transform(sphere, s);
	xs = new_intersections_list();
	intersect(xs, sphere, ray);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->intersections[0]->t, ==, 3);
	munit_assert_float(xs->intersections[1]->t, ==, 7);
	destroy_sphere(sphere);
	destroy_intersections_list(xs);
	destroy_ray(ray);
	return (MUNIT_OK);
}

t_tuple	*normal_at(t_sphere *sphere, t_tuple *point)
{
	t_tuple	*diff;
	t_tuple	*null_point;
	t_tuple	*normal;

	null_point = new_point(0, 0, 0);
	diff = subtract_tuples(point, null_point);
	normal = normalize(diff);
	free(diff);
	free(null_point);
	return (normal);
}

MunitResult sphere_test4(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_tuple *point = new_point(1, 0, 0);
	t_tuple *expected = new_vector(1, 0, 0);

	t_tuple *normal = normal_at(sphere, point);
	munit_assert_true(tuple_equals(normal, expected));
	free(normal);
	free(expected);
	free(point);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}

MunitResult sphere_test5(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_tuple *point = new_point(0, 1, 0);
	t_tuple *expected = new_vector(0, 1, 0);

	t_tuple *normal = normal_at(sphere, point);
	munit_assert_true(tuple_equals(normal, expected));
	free(normal);
	free(expected);
	free(point);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}

MunitResult sphere_test6(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_tuple *point = new_point(0, 0, 1);
	t_tuple *expected = new_vector(0, 0, 1);

	t_tuple *normal = normal_at(sphere, point);
	munit_assert_true(tuple_equals(normal, expected));
	free(normal);
	free(expected);
	free(point);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}

MunitResult sphere_test7(const MunitParameter params[], void *fixture)
{
	float value = sqrtf(3) / 3;
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_tuple *point = new_point(value, value, value);
	t_tuple *expected = new_vector(value, value, value);

	t_tuple *normal = normal_at(sphere, point);
	munit_assert_true(tuple_equals(normal, expected));
	free(normal);
	free(expected);
	free(point);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}

MunitResult sphere_test8(const MunitParameter params[], void *fixture)
{
	float value = sqrtf(3) / 3;
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_tuple *point = new_point(value, value, value);
	t_tuple *expected_vect = new_vector(value, value, value);
	t_tuple *expected = normalize(expected_vect);

	t_tuple *normal = normal_at(sphere, point);
	munit_assert_true(tuple_equals(normal, expected));
	free(normal);
	free(expected);
	free(expected_vect);
	free(point);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}
