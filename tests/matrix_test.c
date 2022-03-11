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
	t_matrix44	*matrix = matrix44(initial);
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
	t_matrix44	*matrix1 = matrix44(same);
	t_matrix44	*matrix2 = matrix44(same);
	t_matrix44	*matrix3 = matrix44(different);

	munit_assert_true(matrix44_equals(matrix1, matrix2));
	munit_assert_false(matrix44_equals(matrix1, matrix3));
	munit_assert_false(matrix44_equals(matrix2, matrix3));
	free(matrix1);
	free(matrix2);
	free(matrix3);
	return (MUNIT_OK);
}

MunitResult test26(const MunitParameter params[], void *fixture)
{
	float	same[3][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 },
	};
	float	different[3][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 8 },
	};
	t_matrix33	*matrix1 = matrix33(same);
	t_matrix33	*matrix2 = matrix33(same);
	t_matrix33	*matrix3 = matrix33(different);

	munit_assert_true(matrix33_equals(matrix1, matrix2));
	munit_assert_false(matrix33_equals(matrix1, matrix3));
	munit_assert_false(matrix33_equals(matrix2, matrix3));
	free(matrix1);
	free(matrix2);
	free(matrix3);
	return (MUNIT_OK);
}

MunitResult test27(const MunitParameter params[], void *fixture)
{
	float	same[2][2] = {
		{ 1, 2 },
		{ 4, 5 },
	};
	float	different[2][2] = {
		{ 1, 2 },
		{ 4, 6 },
	};
	t_matrix22	*matrix1 = matrix22(same);
	t_matrix22	*matrix2 = matrix22(same);
	t_matrix22	*matrix3 = matrix22(different);

	munit_assert_true(matrix22_equals(matrix1, matrix2));
	munit_assert_false(matrix22_equals(matrix1, matrix3));
	munit_assert_false(matrix22_equals(matrix2, matrix3));
	free(matrix1);
	free(matrix2);
	free(matrix3);
	return (MUNIT_OK);
}


MunitResult test28(const MunitParameter params[], void *fixture)
{
	t_matrix44 *a = matrix44((float[4][4]) {
			{ 1 , 2 , 3 , 4 },
			{ 5 , 6 , 7 , 8 },
			{ 9 , 8 , 7 , 6 },
			{ 5 , 4 , 3 , 2 },
			});
	t_matrix44 *b = matrix44((float[4][4]) {
			{ -2, 1, 2, 3 },
			{  3, 2, 1, -1},
			{  4, 3, 6, 5 },
			{  1, 2, 7, 8 },
			});
	t_matrix44 *expected = matrix44((float[4][4]) {
			{ 20, 22 , 50 , 48 },
			{ 44, 54 , 114, 108},
			{ 40, 58 , 110, 102},
			{ 16, 26 , 46 , 42 },
			});

	t_matrix44 *result = matrix44_multiply(a, b);
	munit_assert_true(matrix44_equals(result, expected));
	free(a);
	free(b);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test29(const MunitParameter params[], void *fixture)
{
	t_matrix44 *a = matrix44((float[4][4]) {
			{ 1 , 2 , 3 , 4 },
			{ 2 , 4 , 4 , 2 },
			{ 8 , 6 , 4 , 1 },
			{ 0 , 0 , 0 , 1 },
			});
	t_tuple *b = new_tuple(1, 2, 3, 1);
	t_tuple *expected = new_tuple(18, 24, 33, 1);

	t_tuple *result = matrix44_multiply_tuple(a, b);
	munit_assert_true(tuple_equals(result, expected));
	free(a);
	free(b);
	free(result);
	free(expected);
	return (MUNIT_OK);
}

MunitResult test30(const MunitParameter params[], void *fixture)
{
	t_matrix44 *a = matrix44((float[4][4]) {
			{ 0 , 1 , 2 , 3 },
			{ 1 , 2 , 4 , 8 },
			{ 2 , 4 , 8 , 16 },
			{ 4 , 8 ,16 , 32 },
			});
	t_matrix44 *b = identity_matrix44();

	t_matrix44 *result = matrix44_multiply(a, b);
	munit_assert_true(matrix44_equals(result, a));
	free(a);
	free(b);
	free(result);
	return (MUNIT_OK);
}

MunitResult test31(const MunitParameter params[], void *fixture)
{
	t_matrix44 *a = identity_matrix44();
	t_tuple *b = new_tuple(1, 2, 3, 4);

	t_tuple *result = matrix44_multiply_tuple(a, b);
	munit_assert_true(tuple_equals(result, b));
	free(a);
	free(b);
	free(result);
	return (MUNIT_OK);
}

MunitResult test32(const MunitParameter params[], void *fixture)
{
	t_matrix44 *a = matrix44((float [4][4]) {
		{ 0 , 9 , 3 , 0 },
		{ 9 , 8 , 0 , 8 },
		{ 1 , 8 , 5 , 3 },
		{ 0 , 0 , 5 , 8 },
	});

	t_matrix44 *expected = matrix44((float [4][4]) {
		{ 0 , 9 , 1 , 0 },
		{ 9 , 8 , 8 , 0 },
		{ 3 , 0 , 5 , 5 },
		{ 0 , 8 , 3 , 8 },
	});
	t_matrix44 *result = transpose(a);
	munit_assert_true(matrix44_equals(result, expected));
	free(expected);
	free(a);
	return (MUNIT_OK);
}

MunitResult test33(const MunitParameter params[], void *fixture)
{
	t_matrix44 *a = identity_matrix44();
	t_matrix44 *b = identity_matrix44();
	t_matrix44 *result = transpose(a);
	munit_assert_true(matrix44_equals(result, b));
	free(a);
	free(b);
	return (MUNIT_OK);
}

MunitResult test34(const MunitParameter params[], void *fixture)
{
	t_matrix22 *a = matrix22((float [2][2]){
			{ 1, 5},
			{-3, 2},
		});
	float result = determinant22(a);
	munit_assert_float(result, ==, 17);
	return (MUNIT_OK);
}
