#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include <math.h>

MunitResult test24(const MunitParameter params[], void *fixture)
{
	float	initial[4][4] = {
		{    1,    2,    3,    4 },
		{  5.5,  6.5,  7.5,  8.5 },
		{    9,   10,   11,   12 },
		{ 13.5, 14.5, 15.5, 16.5 },
	};
	t_matrix	*matrix = new_matrix(4, initial);
	munit_assert_float(matrix->data[0][0], ==, 1);
	munit_assert_float(matrix->data[0][3], ==, 4);
	munit_assert_float(matrix->data[1][0], ==, 5.5);
	munit_assert_float(matrix->data[1][2], ==, 7.5);
	munit_assert_float(matrix->data[2][2], ==, 11);
	munit_assert_float(matrix->data[3][0], ==, 13.5);
	munit_assert_float(matrix->data[3][2], ==, 15.5);
	free(matrix);
	return (MUNIT_OK);
}


MunitResult test25(const MunitParameter params[], void *fixture)
{
	float	same[4][4] = {
		{    1,    2,    3,    4 },
		{  5.5,  6.5,  7.5,  8.5 },
		{    9,   10,   11,   12 },
		{ 13.5, 14.5, 15.5, 16.5 },
	};
	float	different[4][4] = {
		{    1,    2,    3,    4 },
		{  5.5,  6.5,  7.5,  8.5 },
		{    9,   10,   11,   12 },
		{ 13.5, 14.5, 15.6, 16.5 },
	};
	t_matrix	*matrix1 = new_matrix(4, same);
	t_matrix	*matrix2 = new_matrix(4, same);
	t_matrix	*matrix3 = new_matrix(4, different);

	munit_assert_true(matrix_equals(matrix1, matrix2));
	munit_assert_false(matrix_equals(matrix1, matrix3));
	munit_assert_false(matrix_equals(matrix2, matrix3));
	free(matrix1);
	free(matrix2);
	free(matrix3);
	return (MUNIT_OK);
}

MunitResult test26(const MunitParameter params[], void *fixture)
{
	float	same[4][4] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 },
	};
	float	different[4][4] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 8 },
	};
	t_matrix	*matrix1 = new_matrix(3, same);
	t_matrix	*matrix2 = new_matrix(3, same);
	t_matrix	*matrix3 = new_matrix(3, different);

	munit_assert_true(matrix_equals(matrix1, matrix2));
	munit_assert_false(matrix_equals(matrix1, matrix3));
	munit_assert_false(matrix_equals(matrix2, matrix3));
	free(matrix1);
	free(matrix2);
	free(matrix3);
	return (MUNIT_OK);
}

MunitResult test27(const MunitParameter params[], void *fixture)
{
	float	same[4][4] = {
		{ 1, 2 },
		{ 4, 5 },
	};
	float	different[4][4] = {
		{ 1, 2 },
		{ 4, 6 },
	};
	t_matrix	*matrix1 = new_matrix(2, same);
	t_matrix	*matrix2 = new_matrix(2, same);
	t_matrix	*matrix3 = new_matrix(2, different);

	munit_assert_true(matrix_equals(matrix1, matrix2));
	munit_assert_false(matrix_equals(matrix1, matrix3));
	munit_assert_false(matrix_equals(matrix2, matrix3));
	free(matrix1);
	free(matrix2);
	free(matrix3);
	return (MUNIT_OK);
}


MunitResult test28(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(4, (float[4][4]) {
			{ 1 , 2 , 3 , 4 },
			{ 5 , 6 , 7 , 8 },
			{ 9 , 8 , 7 , 6 },
			{ 5 , 4 , 3 , 2 },
			});
	t_matrix *b = new_matrix(4, (float[4][4]) {
			{ -2, 1, 2, 3 },
			{  3, 2, 1, -1},
			{  4, 3, 6, 5 },
			{  1, 2, 7, 8 },
			});
	t_matrix *expected = new_matrix(4, (float[4][4]) {
			{ 20, 22 , 50 , 48 },
			{ 44, 54 , 114, 108},
			{ 40, 58 , 110, 102},
			{ 16, 26 , 46 , 42 },
			});

	t_matrix *result = matrix_multiply(a, b);
	munit_assert_true(matrix_equals(result, expected));
	free(a);
	free(b);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test29(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(4, (float[4][4]) {
			{ 1 , 2 , 3 , 4 },
			{ 2 , 4 , 4 , 2 },
			{ 8 , 6 , 4 , 1 },
			{ 0 , 0 , 0 , 1 },
			});
	t_tuple *b = new_tuple(1, 2, 3, 1);
	t_tuple *expected = new_tuple(18, 24, 33, 1);

	t_tuple *result = matrix_multiply_tuple(a, b);
	munit_assert_true(tuple_equals(result, expected));
	free(a);
	free(b);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test30(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(4, (float[4][4]) {
			{ 0 , 1 , 2 , 3 },
			{ 1 , 2 , 4 , 8 },
			{ 2 , 4 , 8 , 16 },
			{ 4 , 8 ,16 , 32 },
			});
	t_matrix *b = identity_matrix();

	t_matrix *result = matrix_multiply(a, b);
	munit_assert_true(matrix_equals(result, a));
	free(a);
	free(b);
	free(result);
	return (MUNIT_OK);
}

MunitResult test31(const MunitParameter params[], void *fixture)
{
	t_matrix *a = identity_matrix();
	t_tuple *b = new_tuple(1, 2, 3, 4);

	t_tuple *result = matrix_multiply_tuple(a, b);
	munit_assert_true(tuple_equals(result, b));
	free(a);
	free(b);
	free(result);
	return (MUNIT_OK);
}

MunitResult test32(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(4, (float [4][4]) {
		{ 0 , 9 , 3 , 0 },
		{ 9 , 8 , 0 , 8 },
		{ 1 , 8 , 5 , 3 },
		{ 0 , 0 , 5 , 8 },
	});

	t_matrix *expected = new_matrix(4, (float [4][4]) {
		{ 0 , 9 , 1 , 0 },
		{ 9 , 8 , 8 , 0 },
		{ 3 , 0 , 5 , 5 },
		{ 0 , 8 , 3 , 8 },
	});
	t_matrix *result = transpose(a);
	munit_assert_true(matrix_equals(result, expected));
	free(expected);
	free(a);
	return (MUNIT_OK);
}

MunitResult test33(const MunitParameter params[], void *fixture)
{
	t_matrix *a = identity_matrix();
	t_matrix *b = identity_matrix();
	t_matrix *result = transpose(a);
	munit_assert_true(matrix_equals(result, b));
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test34(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(2, (float [4][4]){
			{ 1, 5},
			{-3, 2},
		});
	float result = determinant(a);
	munit_assert_float(result, ==, 17);
	return (MUNIT_OK);
}

MunitResult test35(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(3, (float[4][4]) {
			{ 1 , 5 , 0 },
			{ -3, 2 , 7 },
			{ 0 , 6 , -3},
			});
	t_matrix *expected = new_matrix(2, (float[4][4]) {
			{ -3, 2 },
			{ 0 , 6 },
			});

	t_matrix *result = submatrix(a, 0, 2);
	munit_assert_true(matrix_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test36(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(4, (float[4][4]) {
			{ -6 , 1 , 1 , 6 },
			{ -8 , 5 , 8 , 6 },
			{ -1 , 0 , 8 , 2 },
			{ -7 , 1 , -1, 1 },
			});
	t_matrix *expected = new_matrix(3, (float[4][4]) {
			{ -6 , 1 , 6 },
			{ -8 , 8 , 6 },
			{ -7 ,-1 , 1 },
			});

	t_matrix *result = submatrix(a, 2, 1);
	munit_assert_true(matrix_equals(result, expected));
	return (MUNIT_OK);
}

MunitResult test37(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(3, (float[4][4]) {
			{ 3 , 5 , 0 },
			{ 2 ,-1 ,-7 },
			{ 6 ,-1 , 5 },
			});

	float result = minor(a, 1, 0);
	munit_assert_float(result, ==, 25);
	return (MUNIT_OK);
}

MunitResult test38(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(3, (float[4][4]){
		{ 3 ,  5 ,  0 },
		{ 2 , -1 , -7 },
		{ 6 , -1 ,  5 },
		});

	munit_assert_float(minor(a, 0, 0), ==, -12);
	munit_assert_float(cofactor(a, 0, 0), ==, -12);
	munit_assert_float(minor(a, 1, 0), ==, 25);
	munit_assert_float(cofactor(a, 1, 0), ==, -25);
	return (MUNIT_OK);
}

MunitResult test39(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(3, (float[4][4]) {
			{ 1 , 2 , 6 },
			{ -5, 8 , -4},
			{ 2 , 6 , 4 },
			});
	munit_assert_float(cofactor(a, 0, 0), ==, 56);
	munit_assert_float(cofactor(a, 0, 1), ==, 12);
	munit_assert_float(cofactor(a, 0, 2), ==, -46);
	munit_assert_float(determinant(a), ==, -196);
	return (MUNIT_OK);
}

MunitResult test40(const MunitParameter params[], void *fixture)
{
	t_matrix *a = new_matrix(4, (float[4][4]){
			{ -2, -8,  3,  5 },
			{ -3,  1,  7,  3 },
			{  1,  2, -9,  6 },
			{ -6,  7,  7, -9 },
			});

	munit_assert_float(cofactor(a, 0, 0), ==, 690);
	munit_assert_float(cofactor(a, 0, 1), ==, 447);
	munit_assert_float(cofactor(a, 0, 2), ==, 210);
	munit_assert_float(cofactor(a, 0, 3), ==, 51);
	munit_assert_float(determinant(a), ==, -4071);
	return (MUNIT_OK);
}
