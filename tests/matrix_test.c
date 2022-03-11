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
	return (MUNIT_OK);
}
