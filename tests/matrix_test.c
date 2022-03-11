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
	return (MUNIT_OK);
}
