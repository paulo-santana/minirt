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
	return (MUNIT_OK);
}

MunitResult sphere_test3(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_ray *ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_matrix *t = translation(2, 3, 4);
	t_intersections *xs;

	set_transform(sphere, t);
	xs = new_intersections_list();
	intersect(xs, sphere, ray);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->intersections[0]->t, ==, 3);
	munit_assert_float(xs->intersections[1]->t, ==, 7);
	free(t);
	destroy_sphere(sphere);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}
