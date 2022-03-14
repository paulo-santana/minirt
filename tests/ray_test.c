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

t_intersections *new_intersections_list(void)
{
	t_intersections	*intersections;

	intersections = malloc(sizeof(t_intersections));
	intersections->count = 0;
	intersections->size = 50;
	intersections->intersections = malloc(sizeof(t_intersection *) * 50);
	return (intersections);
}

void	destroy_intersections_list(t_intersections *intersections)
{
	free(intersections->intersections);
	free(intersections);
}

MunitResult test62(const MunitParameter params[], void *fixture)
{
	t_intersections	*intersections;

	intersections = new_intersections_list();
	t_ray *r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersections *xs = intersect(intersections, s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->intersections[0]->t, ==, 4.0);
	munit_assert_float(xs->intersections[1]->t, ==, 6.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test63(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 1, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersections *inters;

	inters = new_intersections_list();
	t_intersections *xs = intersect(inters, s, r);
	munit_assert_int(xs->count, ==, 1);
	munit_assert_float(xs->intersections[0]->t, ==, 5.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test64(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 2, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersections *inters;

	inters = new_intersections_list();
	t_intersections *xs = intersect(inters, s, r);
	munit_assert_int(xs->count, ==, 0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test65(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersections *inters;

	inters = new_intersections_list();
	t_intersections *xs = intersect(inters, s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->intersections[0]->t, ==, -1.0);
	munit_assert_float(xs->intersections[1]->t, ==, 1.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test66(const MunitParameter params[], void *fixture)
{
	t_ray *r = new_ray(new_point(0, 0, 5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersections *inters;

	inters = new_intersections_list();
	t_intersections *xs = intersect(inters, s, r);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_float(xs->intersections[0]->t, ==, -6.0);
	munit_assert_float(xs->intersections[1]->t, ==, -4.0);
	free(r->origin);
	free(r->direction);
	free(r);
	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test67(const MunitParameter params[], void *fixture)
{
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersection *intersection = new_intersection(3.5, s, OBJ_SPHERE);
	t_intersections *inters;

	inters = new_intersections_list();
	munit_assert_float(intersection->t, ==, 3.5);
	munit_assert_ptr_equal(intersection->object, s);
	munit_assert_int(intersection->object_type, ==, OBJ_SPHERE);
	free(s->position);
	free(s);
	free(intersection);
	return (MUNIT_OK);
}
