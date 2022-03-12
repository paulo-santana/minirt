#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include <math.h>

#define PARAMS const MunitParameter params[], void *fixture

MunitResult test1(PARAMS);
MunitResult test2(PARAMS);
MunitResult test3(PARAMS);
MunitResult test4(PARAMS);
MunitResult test5(PARAMS);
MunitResult test6(PARAMS);
MunitResult test7(PARAMS);
MunitResult test8(PARAMS);
MunitResult test9(PARAMS);
MunitResult test10(PARAMS);
MunitResult test11(PARAMS);
MunitResult test12(PARAMS);
MunitResult test13(PARAMS);
MunitResult test14(PARAMS);
MunitResult test15(PARAMS);
MunitResult test16(PARAMS);
MunitResult test17(PARAMS);
MunitResult test18(PARAMS);
MunitResult test19(PARAMS);
MunitResult test20(PARAMS);
MunitResult test21(PARAMS);
MunitResult test22(PARAMS);
MunitResult test23(PARAMS);
MunitResult test24(PARAMS);
MunitResult test25(PARAMS);
MunitResult test26(PARAMS);
MunitResult test27(PARAMS);
MunitResult test28(PARAMS);
MunitResult test29(PARAMS);
MunitResult test30(PARAMS);
MunitResult test31(PARAMS);
MunitResult test32(PARAMS);
MunitResult test33(PARAMS);
MunitResult test34(PARAMS);
MunitResult test35(PARAMS);
MunitResult test36(PARAMS);
MunitResult test37(PARAMS);
MunitResult test38(PARAMS);
MunitResult test39(PARAMS);
MunitResult test40(PARAMS);
MunitResult test41(PARAMS);
MunitResult test42(PARAMS);
MunitResult test43(PARAMS);
MunitResult test44(PARAMS);
MunitResult test45(PARAMS);
MunitResult test46(PARAMS);
MunitResult test47(PARAMS);
MunitResult test48(PARAMS);
MunitResult test49(PARAMS);
MunitResult test50(PARAMS);
MunitResult test51(PARAMS);

int main(int argc, char **argv) {
	MunitTest tuple_tests[] = {
		{ "/is_point() and is_vector()", test1, NULL, NULL, 0, NULL },
		{ "/is_point() and is_vector()", test2, NULL, NULL, 0, NULL },
		{ "/new_point() creates a point", test3, NULL, NULL, 0, NULL },
		{ "/new_vector() creates a vector", test4, NULL, NULL, 0, NULL },
		{ "/add_tuples() point + vector", test5, NULL, NULL, 0, NULL },
		{ "/add_tuples() vector + vector", test6, NULL, NULL, 0, NULL },
		{ "/add_tuples() point + point makes no sense", test7, NULL, NULL, 0, NULL },
		{ "/subtract_tuples() point - point = vector", test8, NULL, NULL, 0, NULL },
		{ "/subtract_tuples() point - vector = point", test9, NULL, NULL, 0, NULL },
		{ "/negate_tuple() neagtes a vector", test10, NULL, NULL, 0, NULL },
		{ "/multiply_scalar() multplies a tuple by a scalar value", test11, NULL, NULL, 0, NULL },
		{ "/multiply_scalar() multplies a tuple by a fraction", test12, NULL, NULL, 0, NULL },
		{ "/divide_scalar() divides a tuple by a scalar value", test13, NULL, NULL, 0, NULL },
		{ "/magnitude() calculates correctly", test14, NULL, NULL, 0, NULL },
		{ "/normalize() does what it says", test15, NULL, NULL, 0, NULL },
		{ "/the magnitude of a normalized vector is 1", test16, NULL, NULL, 0, NULL },
		{ "/dot()", test17, NULL, NULL, 0, NULL },
		{ "/cross()", test18, NULL, NULL, 0, NULL },
		{ "/new_color()", test19, NULL, NULL, 0, NULL },
		{ "/add_colors()", test20, NULL, NULL, 0, NULL },
		{ "/subtract_colors()", test21, NULL, NULL, 0, NULL },
		{ "/multiply_scalar_color()", test22, NULL, NULL, 0, NULL },
		{ "/multiply_colors()", test23, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitTest matrix_tests[] = {
		{ "/new_matrix(size, initial_values)", test24, NULL, NULL, 0, NULL },
		{ "/matrix_equals(4x4, 4x4)", test25, NULL, NULL, 0, NULL },
		{ "/matrix_equals(3x3, 3x3)", test26, NULL, NULL, 0, NULL },
		{ "/matrix_equals(2x2, 2x2)", test27, NULL, NULL, 0, NULL },
		{ "/matrix_multiply(4x4, 4x4)", test28, NULL, NULL, 0, NULL },
		{ "/matrix_multiply_tuple(4x4, tuple)", test29, NULL, NULL, 0, NULL },
		{ "/identity_matrix()", test30, NULL, NULL, 0, NULL },
		{ "/identity_matrix() multiply a tuple", test31, NULL, NULL, 0, NULL },
		{ "/transponse()", test32, NULL, NULL, 0, NULL },
		{ "/transponse(identity_matrix)", test33, NULL, NULL, 0, NULL },
		{ "/determinant(2x2)", test34, NULL, NULL, 0, NULL },
		{ "/submatrix(3x3) == 2x2", test35, NULL, NULL, 0, NULL },
		{ "/submatrix(4x4) == 3x3", test36, NULL, NULL, 0, NULL },
		{ "/minor(3x3)", test37, NULL, NULL, 0, NULL },
		{ "/cofactor(3x3)", test38, NULL, NULL, 0, NULL },
		{ "/determinant(3x3)", test39, NULL, NULL, 0, NULL },
		{ "/determinant(4x4)", test40, NULL, NULL, 0, NULL },
		{ "/is_invertible(4x4)", test41, NULL, NULL, 0, NULL },
		{ "/is_invertible(4x4) returns false", test42, NULL, NULL, 0, NULL },
		{ "/inverse() works", test43, NULL, NULL, 0, NULL },
		{ "/inverse() works again", test44, NULL, NULL, 0, NULL },
		{ "/inverse() works again again", test45, NULL, NULL, 0, NULL },
		{ "/multiplying by the inverse() is the same as dividing", test46, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitTest matrix_transform_tests[] = {
		{ "/translation() moves a point", test47, NULL, NULL, 0, NULL },
		{ "/invserse(translation()) moves a point to the oposite direction", test48, NULL, NULL, 0, NULL },
		{ "/translation() * a vector doesn't change it", test49, NULL, NULL, 0, NULL },
		{ "/scaling() scales a point", test50, NULL, NULL, 0, NULL },
		{ "/scaling() scales a vector", test51, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};
	MunitSuite tuple_suite = {
		"/tuples",
		tuple_tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	MunitSuite matrix_suite = {
		"/matrices",
		matrix_tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	MunitSuite matrix_transform_suite = {
		"/matrices/tranform",
		matrix_transform_tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	MunitSuite suites[] = {
		tuple_suite,
		matrix_suite,
		matrix_transform_suite,
		NULL,
	};

	MunitSuite suite = {
		"",
		NULL,
		suites,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};
	return (munit_suite_main(&suite, NULL, argc, argv));
}
