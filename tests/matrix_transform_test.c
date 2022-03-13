#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "../src/debug.h"
#include <math.h>

MunitResult test47(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = translation(5, -3, 2);
	t_tuple *p = new_point(-3, 4, 5);
	
	t_tuple *result = matrix_multiply_tuple(transform, p);
	t_tuple *expected = new_point(2, 1, 7);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test48(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = translation(5, -3, 2);
	t_matrix *inv = inverse(transform);
	t_tuple *p = new_point(-3, 4, 5);
	
	t_tuple *result = matrix_multiply_tuple(inv, p);
	t_tuple *expected = new_point(-8, 7, 3);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test49(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = translation(5, -3, 2);
	t_tuple *p = new_vector(-3, 4, 5);
	
	t_tuple *result = matrix_multiply_tuple(transform, p);
	t_tuple *expected = new_vector(-3, 4, 5);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test50(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = scaling(2, 3, 4);
	t_tuple *p = new_point(-4, 6, 8);
	t_tuple *expected = new_point(-8, 18, 32);

	t_tuple *result = matrix_multiply_tuple(transform, p);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test51(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = scaling(2, 3, 4);
	t_tuple *v = new_vector(-4, 6, 8);
	t_tuple *expected = new_vector(-8, 18, 32);

	t_tuple *result = matrix_multiply_tuple(transform, v);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test52(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = scaling(2, 3, 4);
	t_matrix *inv = inverse(transform);
	t_tuple *v = new_vector(-4, 6, 8);
	t_tuple *expected = new_vector(-2, 2, 2);

	t_tuple *result = matrix_multiply_tuple(inv, v);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test53(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(0, 1, 0);
	t_matrix *half_quarter = rotation_x(M_PI_4);
	t_matrix *full_quarter = rotation_x(M_PI_2);

	t_tuple *half_quarter_expected = new_point(0, M_SQRT2 / 2, M_SQRT2 / 2);
	t_tuple *full_quarter_expected = new_point(0, 0, 1);

	t_tuple *half_quarter_result = matrix_multiply_tuple(half_quarter, p);
	t_tuple *full_quarter_result = matrix_multiply_tuple(full_quarter, p);
	munit_assert_true(tuple_equals(half_quarter_result, half_quarter_expected));
	munit_assert_true(tuple_equals(full_quarter_result, full_quarter_expected));
	return (MUNIT_OK);
}

MunitResult test54(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(0, 1, 0);
	t_matrix *half_quarter = rotation_x(M_PI_4);
	t_matrix *inv = inverse(half_quarter);

	t_tuple *expected = new_point(0, M_SQRT2 / 2, -M_SQRT2 / 2);

	t_tuple *result = matrix_multiply_tuple(inv, p);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test55(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(0, 0, 1);
	t_matrix *half_quarter = rotation_y(M_PI_4);
	t_matrix *full_quarter = rotation_y(M_PI_2);

	t_tuple *half_quarter_expected = new_point(M_SQRT2 / 2, 0, M_SQRT2 / 2);
	t_tuple *full_quarter_expected = new_point(1, 0, 0);

	t_tuple *half_quarter_result = matrix_multiply_tuple(half_quarter, p);
	t_tuple *full_quarter_result = matrix_multiply_tuple(full_quarter, p);
	munit_assert_true(tuple_equals(half_quarter_result, half_quarter_expected));
	munit_assert_true(tuple_equals(full_quarter_result, full_quarter_expected));
	return (MUNIT_OK);
}

MunitResult test56(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(0, 1, 0);
	t_matrix *half_quarter = rotation_z(M_PI_4);
	t_matrix *full_quarter = rotation_z(M_PI_2);

	t_tuple *half_quarter_expected = new_point(-M_SQRT2 / 2, M_SQRT2 / 2, 0);
	t_tuple *full_quarter_expected = new_point(-1, 0, 0);

	t_tuple *half_quarter_result = matrix_multiply_tuple(half_quarter, p);
	t_tuple *full_quarter_result = matrix_multiply_tuple(full_quarter, p);
	munit_assert_true(tuple_equals(half_quarter_result, half_quarter_expected));
	munit_assert_true(tuple_equals(full_quarter_result, full_quarter_expected));
	return (MUNIT_OK);
}
