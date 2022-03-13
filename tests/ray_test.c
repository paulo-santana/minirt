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
	return (MUNIT_OK);
}
