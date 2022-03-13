#include "munit/munit.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "ray/ray.h"
#include <stdlib.h>

MunitResult test60(const MunitParameter params[], void *fixture)
{
	t_tuple	*origin = new_point(1, 2, 3);
	t_tuple *direction = new_vector(4, 5, 6);

	t_ray *r = new_ray(origin, direction);
	munit_assert_true(tuple_equals(r->origin, origin));
	munit_assert_true(tuple_equals(r->direction, direction));
	free(origin);
	free(direction);
	free(r);
	return (MUNIT_OK);
}

MunitResult test61(const MunitParameter params[], void *fixture)
{
	t_tuple *expected;
	t_tuple	*origin = new_point(2, 3, 4);
	t_tuple *direction = new_vector(1, 0, 0);

	t_ray *r = new_ray(origin, direction);
	t_tuple *pos = position(r, 0);
	munit_assert_true(tuple_equals(pos, origin));
	free(pos);

	pos = position(r, 1);
	expected = new_point(3, 3, 4);
	munit_assert_true(tuple_equals(pos, expected));
	free(pos);
	free(expected);

	pos = position(r, -1);
	expected = new_point(1, 3, 4);
	munit_assert_true(tuple_equals(pos, expected));
	free(pos);
	free(expected);

	pos = position(r, 2.5);
	expected = new_point(4.5, 3, 4);
	munit_assert_true(tuple_equals(pos, expected));
	free(pos);
	free(expected);
	free(r);
	free(origin);
	free(direction);
	return (MUNIT_OK);
}

// sphere util

t_sphere	*new_sphere(t_tuple *position, float radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->position = position;
	sphere->radius = radius;
	return (sphere);
}

MunitResult test62(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);

	t_intersections *xs = intersect(s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->distances[0], ==, 4.0);
	munit_assert_float(xs->distances[1], ==, 6.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	free(xs);
	return (MUNIT_OK);
}

MunitResult test63(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 1, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);

	t_intersections *xs = intersect(s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->distances[0], ==, 5.0);
	munit_assert_float(xs->distances[1], ==, 5.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	free(xs);
	return (MUNIT_OK);
}

MunitResult test64(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 2, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);

	t_intersections *xs = intersect(s, r);
	munit_assert_int(xs->count, ==, 0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	free(xs);
	return (MUNIT_OK);
}

MunitResult test65(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);

	t_intersections *xs = intersect(s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->distances[0], ==, -1.0);
	munit_assert_float(xs->distances[1], ==, 1.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	free(xs);
	return (MUNIT_OK);
}

MunitResult test66(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 0, 5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);

	t_intersections *xs = intersect(s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->distances[0], ==, -6.0);
	munit_assert_float(xs->distances[1], ==, -4.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	free(xs);
	return (MUNIT_OK);
}
