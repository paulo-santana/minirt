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

int main(int argc, char **argv) {
	MunitTest tests[] = {
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
