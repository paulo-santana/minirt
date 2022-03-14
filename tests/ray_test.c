#include "matrix/matrix.h"
#include "munit/munit.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
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

t_intersections *new_intersections_list(void)
{
	t_intersections	*intersections;

	intersections = malloc(sizeof(t_intersections));
	intersections->count = 0;
	intersections->size = 50;
	intersections->is_sorted = 0;
	intersections->intersections = malloc(sizeof(t_intersection *) * 50);
	return (intersections);
}

void	destroy_intersections_list(t_intersections *inters)
{
	while (inters->count--)
		free(inters->intersections[inters->count]);
	free(inters->intersections);
	free(inters);
}

MunitResult test62(const MunitParameter params[], void *fixture)
{
	t_intersections	*xs;

	xs = new_intersections_list();
	t_ray *r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);

	intersect(xs, s, r);
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
	t_intersections *xs;

	xs = new_intersections_list();
	intersect(xs, s, r);
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
	t_intersections *xs;

	xs = new_intersections_list();
	intersect(xs, s, r);
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
	t_intersections *xs;

	xs = new_intersections_list();
	intersect(xs, s, r);
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
	t_intersections *xs;

	xs = new_intersections_list();
	intersect(xs, s, r);
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

	munit_assert_float(intersection->t, ==, 3.5);
	munit_assert_ptr_equal(intersection->object, s);
	munit_assert_int(intersection->object_type, ==, OBJ_SPHERE);
	free(s->position);
	free(s);
	free(intersection);
	return (MUNIT_OK);
}

MunitResult test68(const MunitParameter params[], void *fixture)
{
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersection *i1 = new_intersection(1, s, OBJ_SPHERE);
	t_intersection *i2 = new_intersection(2, s, OBJ_SPHERE);
	t_intersections *xs = new_intersections_list();

	add_intersection(xs, i1);
	add_intersection(xs, i2);
	munit_assert_int(xs->count, ==, 2);
	munit_assert_ptr_equal(xs->intersections[0]->object, s);
	munit_assert_ptr_equal(xs->intersections[1]->object, s);
	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test69(const MunitParameter params[], void *fixture)
{
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersection *i1 = new_intersection(1, s, OBJ_SPHERE);
	t_intersection *i2 = new_intersection(2, s, OBJ_SPHERE);
	t_intersections *xs = new_intersections_list();

	add_intersection(xs, i1);
	add_intersection(xs, i2);

	t_intersection *result = hit(xs);
	munit_assert_ptr_equal(result, i1);

	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test70(const MunitParameter params[], void *fixture)
{
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersection *i1 = new_intersection(-1, s, OBJ_SPHERE);
	t_intersection *i2 = new_intersection(1, s, OBJ_SPHERE);
	t_intersections *xs = new_intersections_list();

	add_intersection(xs, i2);
	add_intersection(xs, i1);

	t_intersection *result = hit(xs);
	munit_assert_ptr_equal(result, i2);

	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test71(const MunitParameter params[], void *fixture)
{
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersection *i1 = new_intersection(-2, s, OBJ_SPHERE);
	t_intersection *i2 = new_intersection(-1, s, OBJ_SPHERE);
	t_intersections *xs = new_intersections_list();

	add_intersection(xs, i2);
	add_intersection(xs, i1);

	t_intersection *result = hit(xs);
	munit_assert_ptr_equal(result, NULL);

	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test72(const MunitParameter params[], void *fixture)
{
	t_sphere *s = new_sphere(new_point(0, 0, 0), 1);
	t_intersection *i1 = new_intersection(5, s, OBJ_SPHERE);
	t_intersection *i2 = new_intersection(7, s, OBJ_SPHERE);
	t_intersection *i3 = new_intersection(-3, s, OBJ_SPHERE);
	t_intersection *i4 = new_intersection(2, s, OBJ_SPHERE);
	t_intersections *xs = new_intersections_list();

	add_intersection(xs, i1);
	add_intersection(xs, i2);
	add_intersection(xs, i3);
	add_intersection(xs, i4);

	t_intersection *result = hit(xs);
	munit_assert_ptr_equal(result, i4);

	free(s->position);
	free(s);
	destroy_intersections_list(xs);
	return (MUNIT_OK);
}

MunitResult test73(const MunitParameter params[], void *fixture)
{
	t_ray *ray = new_ray(new_point(1, 2, 3), new_vector(0, 1, 0));
	t_matrix *mat_translation = translation(3, 4, 5);

	t_ray *result = transform(ray, mat_translation);
	t_tuple *expected_origin = new_point(4, 6, 8);
	t_tuple *expected_diretction = new_vector(0, 1, 0);
	munit_assert_true(tuple_equals(result->origin, expected_origin));
	munit_assert_true(tuple_equals(result->direction, expected_diretction));

	free(ray->origin);
	free(ray->direction);
	free(ray);
	free(mat_translation);
	free(result->origin);
	free(result->direction);
	free(result);
	free(expected_diretction);
	free(expected_origin);
	return (MUNIT_OK);
}

MunitResult test74(const MunitParameter params[], void *fixture)
{
	t_ray *ray = new_ray(new_point(1, 2, 3), new_vector(0, 1, 0));
	t_matrix *mat_translation = scaling(2, 3, 4);

	t_ray *result = transform(ray, mat_translation);
	t_tuple *expected_origin = new_point(2, 6, 12);
	t_tuple *expected_diretction = new_vector(0, 3, 0);
	munit_assert_true(tuple_equals(result->origin, expected_origin));
	munit_assert_true(tuple_equals(result->direction, expected_diretction));

	free(ray->origin);
	free(ray->direction);
	free(ray);
	free(mat_translation);
	free(result->origin);
	free(result->direction);
	free(result);
	free(expected_diretction);
	free(expected_origin);
	return (MUNIT_OK);
}
