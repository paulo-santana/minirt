#include "munit/munit.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"

void destroy_plane(t_shape *shape)
{
	free(shape->transform);
	free(shape->inverse_transform);
	destroy_material(shape->material);
	free(shape);
}

t_tuple *plane_normal_at(t_shape *shape, t_tuple *tuple)
{
	return (new_vector(0, 1, 0));
}

t_shape *new_plane(void)
{
	t_shape *plane;

	plane = new_shape();
	plane->destroy_fn = destroy_plane;
	plane->normal_at = plane_normal_at;
	return (plane);
}

// the normal of a plane is constant everywhere
MunitResult plane_test1(const MunitParameter params[], void *fixture)
{
	t_shape *plane = new_plane();

	t_tuple *p1 = new_point(0, 0, 0);
	t_tuple *p2 = new_point(10, 0, -10);
	t_tuple *p3 = new_point(-5, 0, 150);

	t_tuple *expected = new_vector(0, 1, 0);

	t_tuple *n1 = plane->normal_at(plane, p1);
	t_tuple *n2 = plane->normal_at(plane, p2);
	t_tuple *n3 = plane->normal_at(plane, p3);

	munit_assert_true(tuple_equals(n1, expected));
	munit_assert_true(tuple_equals(n2, expected));
	munit_assert_true(tuple_equals(n3, expected));
	free(n1);
	free(n2);
	free(n3);
	free(p1);
	free(p2);
	free(p3);
	free(expected);
	plane->destroy_fn(plane);
	return MUNIT_OK;
}
