#include "munit/munit.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "ray/ray.h"

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
