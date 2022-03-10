#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"

MunitResult a_tuple_with_w_1_is_a_point(const MunitParameter params[], void *fixture)
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

MunitResult a_tuple_with_w_0_is_a_vector(const MunitParameter params[], void *fixture)
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

MunitResult new_point_creates_tuples_with_w_1(const MunitParameter params[], void *fixture)
{
	t_tuple *result = new_point(4.3, -4.2, 3.1);
	t_tuple *expected = new_tuple(4.3, -4.2, 3.1, 1.0);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult new_vector_creates_tuples_with_w_0(const MunitParameter params[], void *fixture)
{
	t_tuple *result = new_vector(4.3, -4.2, 3.1);
	t_tuple *expected = new_tuple(4.3, -4.2, 3.1, 0.0);

	munit_assert_true(tuple_equals(result, expected));
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test_add_tuples(const MunitParameter params[], void *fixture)
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

MunitResult test_add_tuples2(const MunitParameter params[], void *fixture)
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

MunitResult test_add_tuples3(const MunitParameter params[], void *fixture)
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

MunitResult test_subtract_tuples(const MunitParameter params[], void *fixture)
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

MunitResult test_subtract_tuples2(const MunitParameter params[], void *fixture)
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

MunitResult test_negate_tuple(const MunitParameter params[], void *fixture)
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

MunitResult test_multiply_scalar(const MunitParameter params[], void *fixture)
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

MunitResult test_multiply_scalar2(const MunitParameter params[], void *fixture)
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

int main(int argc, char **argv) {
	MunitTest tests[] = {
		{ "/is_point() and is_vector()", a_tuple_with_w_1_is_a_point, NULL, NULL, 0, NULL },
		{ "/is_point() and is_vector()", a_tuple_with_w_0_is_a_vector, NULL, NULL, 0, NULL },
		{ "/new_point() creates a point", new_point_creates_tuples_with_w_1, NULL, NULL, 0, NULL },
		{ "/new_vector() creates a vector", new_vector_creates_tuples_with_w_0, NULL, NULL, 0, NULL },
		{ "/add_tuples() point + vector", test_add_tuples, NULL, NULL, 0, NULL },
		{ "/add_tuples() vector + vector", test_add_tuples2, NULL, NULL, 0, NULL },
		{ "/add_tuples() point + point makes no sense", test_add_tuples3, NULL, NULL, 0, NULL },
		{ "/subtract_tuples() point - point = vector", test_subtract_tuples, NULL, NULL, 0, NULL },
		{ "/subtract_tuples() point - vector = point", test_subtract_tuples2, NULL, NULL, 0, NULL },
		{ "/negate_tuple() neagtes a vector", test_negate_tuple, NULL, NULL, 0, NULL },
		{ "/multiply_scalar() multplies a tuple by a scalar value", test_multiply_scalar, NULL, NULL, 0, NULL },
		{ "/multiply_scalar() multplies a tuple by a fraction", test_multiply_scalar2, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitSuite suite = {
		"/tuples",
		tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	return (munit_suite_main(&suite, NULL, argc, argv));
}
