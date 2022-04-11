#include "munit/munit.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "shapes/shapes.h"
#include <stdlib.h>

static t_color black = {0,0,0};
static t_color white = {1,1,1};



MunitResult pattern_test1(const MunitParameter params[], void *fixture)
{
	t_pattern *pattern = stripe_pattern(&white, &black);

	munit_assert_ptr(pattern->a, ==, &white);
	munit_assert_ptr(pattern->b, ==, &black);
	return MUNIT_OK;
}

// a stripe pattern is constant in y
MunitResult pattern_test2(const MunitParameter params[], void *fixture)
{
	t_pattern *pattern = stripe_pattern(&white, &black);
	t_color *expected = &white;

	t_tuple *point1 = new_point(0, 0, 0);
	t_tuple *point2 = new_point(0, 1, 0);
	t_tuple *point3 = new_point(0, 2, 0);

	t_color *result1 = stripe_at(point1, pattern);
	t_color *result2 = stripe_at(point2, pattern);
	t_color *result3 = stripe_at(point3, pattern);

	munit_assert_ptr(result1, ==, expected);
	munit_assert_ptr(result2, ==, expected);
	munit_assert_ptr(result3, ==, expected);
	return MUNIT_OK;
}

// a stripe pattern is constant in z
MunitResult pattern_test3(const MunitParameter params[], void *fixture)
{
	t_pattern *pattern = stripe_pattern(&white, &black);
	t_color *expected = &white;

	t_tuple *point1 = new_point(0, 0, 0);
	t_tuple *point2 = new_point(0, 0, 1);
	t_tuple *point3 = new_point(0, 0, 2);

	t_color *result1 = stripe_at(point1, pattern);
	t_color *result2 = stripe_at(point2, pattern);
	t_color *result3 = stripe_at(point3, pattern);

	munit_assert_ptr(result1, ==, expected);
	munit_assert_ptr(result2, ==, expected);
	munit_assert_ptr(result3, ==, expected);
	return MUNIT_OK;
}

// a stripe pattern alternates in x
MunitResult pattern_test4(const MunitParameter params[], void *fixture)
{
	t_pattern *pattern = stripe_pattern(&white, &black);
	t_color *expected1 = &white;
	t_color *expected2 = &white;
	t_color *expected3 = &black;

	t_tuple *point1 = new_point(0, 0, 0);
	t_tuple *point2 = new_point(.5, 0, 0);
	t_tuple *point3 = new_point(1, 0, 0);

	t_color *result1 = stripe_at(point1, pattern);
	t_color *result2 = stripe_at(point2, pattern);
	t_color *result3 = stripe_at(point3, pattern);

	munit_assert_ptr(result1, ==, expected1);
	munit_assert_ptr(result2, ==, expected2);
	munit_assert_ptr(result3, ==, expected3);
	return MUNIT_OK;
}
