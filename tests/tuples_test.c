#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include <math.h>

MunitResult test1(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(4.3, -4.2, 3.1, 1);

	munit_assert_float(a->x, ==, 4.3);
	munit_assert_float(a->y, ==, -4.2);
	munit_assert_float(a->z, ==, 3.1);
	munit_assert_float(a->w, ==, 1.0);
	munit_assert_true(is_point(a));
	munit_assert_false(is_vector(a));
	free(a);
	return (MUNIT_OK);
}

MunitResult test2(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(4.3, -4.2, 3.1, 0);

	munit_assert_float(a->x, ==, 4.3);
	munit_assert_float(a->y, ==, -4.2);
	munit_assert_float(a->z, ==, 3.1);
	munit_assert_float(a->w, ==, 0.0);
	munit_assert_false(is_point(a));
	munit_assert_true(is_vector(a));
	free(a);
	return (MUNIT_OK);
}

MunitResult test3(const MunitParameter params[], void *fixture)
{
	t_tuple *result = new_point(4.3, -4.2, 3.1);
	t_tuple *expected = new_tuple(4.3, -4.2, 3.1, 1.0);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test4(const MunitParameter params[], void *fixture)
{
	t_tuple *result = new_vector(4.3, -4.2, 3.1);
	t_tuple *expected = new_tuple(4.3, -4.2, 3.1, 0.0);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test5(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(3, -2 , 5, 1);
	t_tuple *b = new_tuple(-2, 3 , 1, 0);

	t_tuple *result = add_tuples(a, b);
	t_tuple *expected = new_tuple(1, 1, 6, 1);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test6(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(3, -2 , 5, 0);
	t_tuple *b = new_tuple(-2, 3 , -1, 0);

	t_tuple *result = add_tuples(a, b);
	t_tuple *expected = new_tuple(1, 1, 4, 0);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test7(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(3, -2 , 5, 1);
	t_tuple *b = new_tuple(-2, 3 , -1, 1);

	t_tuple *result = add_tuples(a, b);

	munit_assert_false(is_point(result));
	munit_assert_false(is_vector(result));
	free(result);
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test8(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_point(3, 2, 1);
	t_tuple *b = new_point(5, 6, 7);

	t_tuple *result = subtract_tuples(a, b);
	t_tuple *expected = new_vector(-2, -4, -6);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test9(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_point(3, 2, 1);
	t_tuple *b = new_vector(5, 6, 7);

	t_tuple *result = subtract_tuples(a, b);
	t_tuple *expected = new_point(-2, -4, -6);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test10(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(1, -2, 3, -4);

	t_tuple *result = negate_tuple(a);
	t_tuple *expected = new_tuple(-1, 2, -3, 4);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	free(a);
	return (MUNIT_OK);
}

MunitResult test11(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(1, -2, 3, -4);

	t_tuple *result = multiply_scalar(a, 3.5);
	t_tuple *expected = new_tuple(3.5, -7, 10.5, -14);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	free(a);
	return (MUNIT_OK);
}

MunitResult test12(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(1, -2, 3, -4);

	t_tuple *result = multiply_scalar(a, 0.5);
	t_tuple *expected = new_tuple(0.5, -1, 1.5, -2);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	free(a);
	return (MUNIT_OK);
}

MunitResult test13(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(1, -2, 3, -4);

	t_tuple *result = divide_scalar(a, 2);
	t_tuple *expected = new_tuple(0.5, -1, 1.5, -2);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	free(a);
	return (MUNIT_OK);
}

MunitResult test14(const MunitParameter params[], void *fixture)
{
	float result, expected;
	t_tuple *a;

	a = new_vector(1, 0, 0);
	result = magnitude(a);
	expected = 1.0;
	munit_assert_float(result, ==, expected);
	free(a);

	a = new_vector(0, 1, 0);
	result = magnitude(a);
	expected = 1.0;
	munit_assert_float(result, ==, expected);
	free(a);

	a = new_vector(0, 0, 1);
	result = magnitude(a);
	expected = 1.0;
	munit_assert_float(result, ==, expected);
	free(a);

	a = new_vector(1, 2, 3);
	result = magnitude(a);
	expected = sqrt(14);
	munit_assert_float(result, ==, expected);
	free(a);

	a = new_vector(-1, -2, -3);
	result = magnitude(a);
	expected = sqrt(14);
	munit_assert_float(result, ==, expected);
	free(a);
	return (MUNIT_OK);
}


MunitResult test15(const MunitParameter params[], void *fixture)
{
	t_tuple *a, *norm, *expected;

	a = new_vector(4, 0, 0);
	norm = normalize(a);
	expected = new_vector(1, 0, 0);
	munit_assert_true(tuple_equals(norm, expected));
	free(a);
	free(norm);
	free(expected);

	a = new_vector(1, 2, 3);
	norm = normalize(a);
	expected = new_vector(0.26726, 0.53452, 0.80178);
	munit_assert_true(tuple_equals(norm, expected));
	free(a);
	free(norm);
	free(expected);

	return (MUNIT_OK);
}

MunitResult test16(const MunitParameter params[], void *fixture)
{
	t_tuple *a, *norm;

	a = new_vector(1, 2, 3);
	norm = normalize(a);
	munit_assert_true(fequals(magnitude(norm), 1));
	free(a);
	free(norm);

	return (MUNIT_OK);
}

float	dot(t_tuple *a, t_tuple *b)
{
	return (
		a->x * b->x
		+ a->y * b->y
		+ a->z * b->z
		+ a->w * b->w
	);
}

MunitResult test17(const MunitParameter params[], void *fixture)
{
	t_tuple *a, *b;

	a = new_vector(1, 2, 3);
	b = new_vector(2, 3, 4);
	munit_assert_float(dot(a, b), ==, 20);
	free(a);
	free(b);

	return (MUNIT_OK);
}

MunitResult test18(const MunitParameter params[], void *fixture)
{
	t_tuple *a, *b, *expected, *result;

	a = new_vector(1, 2, 3);
	b = new_vector(2, 3, 4);
	result = cross(a, b);
	expected = new_vector(-1, 2, -1);
	munit_assert_true(tuple_equals(result, expected));
	free(expected);
	free(result);

	result = cross(b, a);
	expected = new_vector(1, -2, 1);
	munit_assert_true(tuple_equals(result, expected));
	free(expected);
	free(result);
	free(a);
	free(b);

	return (MUNIT_OK);
}

MunitResult test19(const MunitParameter params[], void *fixture)
{
	t_color	*color;

	color = new_color(-0.5, 0.4, 1.7);
	munit_assert_float(color->red, ==, -0.5);
	munit_assert_float(color->green, ==, 0.4);
	munit_assert_float(color->blue, ==, 1.7);
	free(color);
	return (MUNIT_OK);
}

MunitResult test20(const MunitParameter params[], void *fixture)
{
	t_color	*a, *b, *result, *expected;

	a = new_color(0.9, 0.6, 0.75);
	b = new_color(0.7, 0.1, 0.25);
	result = add_colors(a, b);
	expected = new_color(1.6, 0.7, 1);
	munit_assert_true(fequals(result->red, expected->red));
	munit_assert_true(fequals(result->green, expected->green));
	munit_assert_true(fequals(result->blue, expected->blue));
	free(a);
	free(result);
	free(expected);
	free(b);
	return (MUNIT_OK);
}

MunitResult test21(const MunitParameter params[], void *fixture)
{
	t_color	*a, *b, *result, *expected;

	a = new_color(0.9, 0.6, 0.75);
	b = new_color(0.7, 0.1, 0.25);
	result = subtract_colors(a, b);
	expected = new_color(0.2, 0.5, 0.5);
	munit_assert_true(fequals(result->red, expected->red));
	munit_assert_true(fequals(result->green, expected->green));
	munit_assert_true(fequals(result->blue, expected->blue));
	free(a);
	free(result);
	free(expected);
	free(b);
	return (MUNIT_OK);
}

MunitResult test22(const MunitParameter params[], void *fixture)
{
	t_color	*a, *result, *expected;

	a = new_color(0.2, 0.3, 0.4);
	result = multiply_scalar_color(a, 2);
	expected = new_color(0.4, 0.6, 0.8);
	munit_assert_true(fequals(result->red, expected->red));
	munit_assert_true(fequals(result->green, expected->green));
	munit_assert_true(fequals(result->blue, expected->blue));
	free(a);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test23(const MunitParameter params[], void *fixture)
{
	t_color	*a, *b, *result, *expected;

	a = new_color(1, 0.2, 0.4);
	b = new_color(0.9, 1, 0.1);
	result = multiply_colors(a, b);
	expected = new_color(0.9, 0.2, 0.04);
	munit_assert_true(fequals(result->red, expected->red));
	munit_assert_true(fequals(result->green, expected->green));
	munit_assert_true(fequals(result->blue, expected->blue));
	free(a);
	free(b);
	free(result);
	free(expected);
	return (MUNIT_OK);
}
