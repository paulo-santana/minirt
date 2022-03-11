#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include <math.h>

#define PARAMS const MunitParameter params[], void *fixture

MunitResult a_tuple_with_w_1_is_a_point(PARAMS);
MunitResult a_tuple_with_w_0_is_a_vector(PARAMS);
MunitResult new_point_creates_tuples_with_w_1(PARAMS);
MunitResult new_vector_creates_tuples_with_w_0(PARAMS);
MunitResult test_add_tuples(PARAMS);
MunitResult test_add_tuples2(PARAMS);
MunitResult test_add_tuples3(PARAMS);
MunitResult test_subtract_tuples(PARAMS);
MunitResult test_subtract_tuples2(PARAMS);
MunitResult test_negate_tuple(PARAMS);
MunitResult test_multiply_scalar(PARAMS);
MunitResult test_multiply_scalar2(PARAMS);
MunitResult test_divide_scalar(PARAMS);
MunitResult test_magnitude1(PARAMS);
MunitResult test_normalize(PARAMS);
MunitResult test_normalize2(PARAMS);
MunitResult test_dot_product(PARAMS);
MunitResult test_cross_product(PARAMS);

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
		{ "/divide_scalar() divides a tuple by a scalar value", test_divide_scalar, NULL, NULL, 0, NULL },
		{ "/magnitude() calculates correctly", test_magnitude1, NULL, NULL, 0, NULL },
		{ "/normalize() does what it says", test_normalize, NULL, NULL, 0, NULL },
		{ "/the magnitude of a normalized vector is 1", test_normalize2, NULL, NULL, 0, NULL },
		{ "/dot()", test_dot_product, NULL, NULL, 0, NULL },
		{ "/cross()", test_cross_product, NULL, NULL, 0, NULL },
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
