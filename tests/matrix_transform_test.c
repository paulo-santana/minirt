#include "matrix/matrix.h"
#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "../src/debug.h"
#include "tuple/tuple.h"
#include <math.h>

MunitResult test47(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = translation(5, -3, 2);
	t_tuple *p = new_point(-3, 4, 5);
	
	t_tuple *result = matrix_multiply_tuple(transform, p);
	t_tuple *expected = new_point(2, 1, 7);

	munit_assert_true(tuple_equals(result, expected));

	free(transform);
	free(p);
	free(result);
	free(expected);
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

	free(transform);
	free(p);
	free(inv);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test49(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = translation(5, -3, 2);
	t_tuple *p = new_vector(-3, 4, 5);
	
	t_tuple *result = matrix_multiply_tuple(transform, p);
	t_tuple *expected = new_vector(-3, 4, 5);

	munit_assert_true(tuple_equals(result, expected));

	free(transform);
	free(p);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test50(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = scaling(2, 3, 4);
	t_tuple *p = new_point(-4, 6, 8);
	t_tuple *expected = new_point(-8, 18, 32);

	t_tuple *result = matrix_multiply_tuple(transform, p);

	munit_assert_true(tuple_equals(result, expected));

	free(transform);
	free(p);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test51(const MunitParameter params[], void *fixture)
{
	t_matrix *transform = scaling(2, 3, 4);
	t_tuple *v = new_vector(-4, 6, 8);
	t_tuple *expected = new_vector(-8, 18, 32);

	t_tuple *result = matrix_multiply_tuple(transform, v);

	munit_assert_true(tuple_equals(result, expected));

	free(transform);
	free(v);
	free(result);
	free(expected);
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

	free(transform);
	free(v);
	free(inv);
	free(result);
	free(expected);
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

	free(p);
	free(half_quarter);
	free(full_quarter);
	free(half_quarter_expected);
	free(full_quarter_expected);
	free(half_quarter_result);
	free(full_quarter_result);
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

	free(half_quarter);
	free(p);
	free(inv);
	free(result);
	free(expected);
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

	free(p);
	free(half_quarter);
	free(full_quarter);
	free(half_quarter_expected);
	free(full_quarter_expected);
	free(half_quarter_result);
	free(full_quarter_result);
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

	free(p);
	free(half_quarter);
	free(full_quarter);
	free(half_quarter_expected);
	free(full_quarter_expected);
	free(half_quarter_result);
	free(full_quarter_result);
	return (MUNIT_OK);
}

MunitResult test57(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(1, 0, 1);
	t_matrix *A = rotation_x(M_PI_2);
	t_matrix *B = scaling(5, 5, 5);
	t_matrix *C = translation(10, 5, 7);

	t_tuple *p2 = matrix_multiply_tuple(A, p);	
	t_tuple *p2_expected = new_point(1, -1, 0);
	munit_assert_true(tuple_equals(p2, p2_expected));

	t_tuple *p3 = matrix_multiply_tuple(B, p2);	
	t_tuple *p3_expected = new_point(5, -5, 0);
	munit_assert_true(tuple_equals(p3, p3_expected));

	t_tuple *p4 = matrix_multiply_tuple(C, p3);	
	t_tuple *p4_expected = new_point(15, 0, 7);
	munit_assert_true(tuple_equals(p4, p4_expected));

	free(p);
	free(A);
	free(B);
	free(C);
	free(p2);
	free(p3);
	free(p4);
	free(p2_expected);
	free(p3_expected);
	free(p4_expected);
	return (MUNIT_OK);
}

MunitResult test58(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(1, 0, 1);
	t_matrix *A = rotation_x(M_PI_2);
	t_matrix *B = scaling(5, 5, 5);
	t_matrix *C = translation(10, 5, 7);

	t_matrix *T = matrix_multiply3(A, B, C);

	t_tuple *p2 = matrix_multiply_tuple(T, p);	
	t_tuple *p2_expected = new_point(15, 0, 7);

	munit_assert_true(tuple_equals(p2, p2_expected));

	free(p);
	free(A);
	free(B);
	free(C);
	free(T);
	free(p2);
	free(p2_expected);
	return (MUNIT_OK);
}

MunitResult test59(const MunitParameter params[], void *fixture)
{
	t_tuple *p = new_point(1, 0, 1);
	t_matrix *A = rotation_x(M_PI_2);
	t_matrix *B = scaling(5, 5, 5);
	t_matrix *C = translation(10, 5, 7);

	t_matrix **Ts = malloc(sizeof(t_matrix *) * 4);
	Ts[0] = A;
	Ts[1] = B;
	Ts[2] = C;
	Ts[3] = NULL;
	t_matrix *T = matrix_multiply_n(Ts);

	t_tuple *p2 = matrix_multiply_tuple(T, p);	
	t_tuple *p2_expected = new_point(15, 0, 7);
	munit_assert_true(tuple_equals(p2, p2_expected));

	free(p);
	free(A);
	free(B);
	free(C);
	free(T);
	free(Ts);
	free(p2);
	free(p2_expected);
	return (MUNIT_OK);
}
