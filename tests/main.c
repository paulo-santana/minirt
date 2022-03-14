#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include <math.h>

#define PARAMS const MunitParameter params[], void *fixture

MunitResult matrix_test1(PARAMS);
MunitResult matrix_test2(PARAMS);
MunitResult matrix_test3(PARAMS);
MunitResult matrix_test4(PARAMS);
MunitResult matrix_test5(PARAMS);
MunitResult matrix_test6(PARAMS);
MunitResult matrix_test7(PARAMS);
MunitResult matrix_test8(PARAMS);
MunitResult matrix_test9(PARAMS);
MunitResult matrix_test10(PARAMS);
MunitResult matrix_test11(PARAMS);
MunitResult matrix_test12(PARAMS);
MunitResult matrix_test13(PARAMS);
MunitResult matrix_test14(PARAMS);
MunitResult matrix_test15(PARAMS);
MunitResult matrix_test16(PARAMS);
MunitResult matrix_test17(PARAMS);
MunitResult matrix_test18(PARAMS);
MunitResult matrix_test19(PARAMS);
MunitResult matrix_test20(PARAMS);
MunitResult matrix_test21(PARAMS);
MunitResult matrix_test22(PARAMS);
MunitResult matrix_test23(PARAMS);
MunitResult tuple_test1(PARAMS);
MunitResult tuple_test2(PARAMS);
MunitResult tuple_test3(PARAMS);
MunitResult tuple_test4(PARAMS);
MunitResult tuple_test5(PARAMS);
MunitResult tuple_test6(PARAMS);
MunitResult tuple_test7(PARAMS);
MunitResult tuple_test8(PARAMS);
MunitResult tuple_test9(PARAMS);
MunitResult tuple_test10(PARAMS);
MunitResult tuple_test11(PARAMS);
MunitResult tuple_test12(PARAMS);
MunitResult tuple_test13(PARAMS);
MunitResult tuple_test14(PARAMS);
MunitResult tuple_test15(PARAMS);
MunitResult tuple_test16(PARAMS);
MunitResult tuple_test17(PARAMS);
MunitResult tuple_test18(PARAMS);
MunitResult tuple_test19(PARAMS);
MunitResult tuple_test20(PARAMS);
MunitResult tuple_test21(PARAMS);
MunitResult tuple_test22(PARAMS);
MunitResult tuple_test23(PARAMS);
MunitResult matrix_transform_test1(PARAMS);
MunitResult matrix_transform_test2(PARAMS);
MunitResult matrix_transform_test3(PARAMS);
MunitResult matrix_transform_test4(PARAMS);
MunitResult matrix_transform_test5(PARAMS);
MunitResult matrix_transform_test6(PARAMS);
MunitResult matrix_transform_test7(PARAMS);
MunitResult matrix_transform_test8(PARAMS);
MunitResult matrix_transform_test9(PARAMS);
MunitResult matrix_transform_test10(PARAMS);
MunitResult matrix_transform_test11(PARAMS);
MunitResult matrix_transform_test12(PARAMS);
MunitResult matrix_transform_test13(PARAMS);
MunitResult ray_test1(PARAMS);
MunitResult ray_test2(PARAMS);
MunitResult ray_test3(PARAMS);
MunitResult ray_test4(PARAMS);
MunitResult ray_test5(PARAMS);
MunitResult ray_test6(PARAMS);
MunitResult ray_test7(PARAMS);
MunitResult ray_test8(PARAMS);
MunitResult ray_test9(PARAMS);
MunitResult ray_test10(PARAMS);
MunitResult ray_test11(PARAMS);
MunitResult ray_test12(PARAMS);
MunitResult ray_test13(PARAMS);
MunitResult ray_test14(PARAMS);
MunitResult ray_test15(PARAMS);
MunitResult sphere_test1(PARAMS);
MunitResult sphere_test2(PARAMS);
MunitResult sphere_test3(PARAMS);

int main(int argc, char **argv) {
	MunitTest tuple_tests[] = {
		{ "/is_point() and is_vector()", tuple_test1, NULL, NULL, 0, NULL },
		{ "/is_point() and is_vector()", tuple_test2, NULL, NULL, 0, NULL },
		{ "/new_point() creates a point", tuple_test3, NULL, NULL, 0, NULL },
		{ "/new_vector() creates a vector", tuple_test4, NULL, NULL, 0, NULL },
		{ "/add_tuples() point + vector", tuple_test5, NULL, NULL, 0, NULL },
		{ "/add_tuples() vector + vector", tuple_test6, NULL, NULL, 0, NULL },
		{ "/add_tuples() point + point makes no sense", tuple_test7, NULL, NULL, 0, NULL },
		{ "/subtract_tuples() point - point = vector", tuple_test8, NULL, NULL, 0, NULL },
		{ "/subtract_tuples() point - vector = point", tuple_test9, NULL, NULL, 0, NULL },
		{ "/negate_tuple() neagtes a vector", tuple_test10, NULL, NULL, 0, NULL },
		{ "/multiply_scalar() multplies a tuple by a scalar value", tuple_test11, NULL, NULL, 0, NULL },
		{ "/multiply_scalar() multplies a tuple by a fraction", tuple_test12, NULL, NULL, 0, NULL },
		{ "/divide_scalar() divides a tuple by a scalar value", tuple_test13, NULL, NULL, 0, NULL },
		{ "/magnitude() calculates correctly", tuple_test14, NULL, NULL, 0, NULL },
		{ "/normalize() does what it says", tuple_test15, NULL, NULL, 0, NULL },
		{ "/the magnitude of a normalized vector is 1", tuple_test16, NULL, NULL, 0, NULL },
		{ "/dot()", tuple_test17, NULL, NULL, 0, NULL },
		{ "/cross()", tuple_test18, NULL, NULL, 0, NULL },
		{ "/new_color()", tuple_test19, NULL, NULL, 0, NULL },
		{ "/add_colors()", tuple_test20, NULL, NULL, 0, NULL },
		{ "/subtract_colors()", tuple_test21, NULL, NULL, 0, NULL },
		{ "/multiply_scalar_color()", tuple_test22, NULL, NULL, 0, NULL },
		{ "/multiply_colors()", tuple_test23, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitTest matrix_tests[] = {
		{ "/new_matrix(size, initial_values)", matrix_test1, NULL, NULL, 0, NULL },
		{ "/matrix_equals(4x4, 4x4)", matrix_test2, NULL, NULL, 0, NULL },
		{ "/matrix_equals(3x3, 3x3)", matrix_test3, NULL, NULL, 0, NULL },
		{ "/matrix_equals(2x2, 2x2)", matrix_test4, NULL, NULL, 0, NULL },
		{ "/matrix_multiply(4x4, 4x4)", matrix_test5, NULL, NULL, 0, NULL },
		{ "/matrix_multiply_tuple(4x4, tuple)", matrix_test6, NULL, NULL, 0, NULL },
		{ "/identity_matrix()", matrix_test7, NULL, NULL, 0, NULL },
		{ "/identity_matrix() multiply a tuple", matrix_test8, NULL, NULL, 0, NULL },
		{ "/transponse()", matrix_test9, NULL, NULL, 0, NULL },
		{ "/transponse(identity_matrix)", matrix_test10, NULL, NULL, 0, NULL },
		{ "/determinant(2x2)", matrix_test11, NULL, NULL, 0, NULL },
		{ "/submatrix(3x3) == 2x2", matrix_test12, NULL, NULL, 0, NULL },
		{ "/submatrix(4x4) == 3x3", matrix_test13, NULL, NULL, 0, NULL },
		{ "/minor(3x3)", matrix_test14, NULL, NULL, 0, NULL },
		{ "/cofactor(3x3)", matrix_test15, NULL, NULL, 0, NULL },
		{ "/determinant(3x3)", matrix_test16, NULL, NULL, 0, NULL },
		{ "/determinant(4x4)", matrix_test17, NULL, NULL, 0, NULL },
		{ "/is_invertible(4x4)", matrix_test18, NULL, NULL, 0, NULL },
		{ "/is_invertible(4x4) returns false", matrix_test19, NULL, NULL, 0, NULL },
		{ "/inverse() works", matrix_test20, NULL, NULL, 0, NULL },
		{ "/inverse() works again", matrix_test21, NULL, NULL, 0, NULL },
		{ "/inverse() works again again", matrix_test22, NULL, NULL, 0, NULL },
		{ "/multiplying by the inverse() is the same as dividing", matrix_test23, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitTest matrix_transform_tests[] = {
		{ "/translation() moves a point", matrix_transform_test1, NULL, NULL, 0, NULL },
		{ "/invserse(translation()) moves a point to the oposite direction", matrix_transform_test2, NULL, NULL, 0, NULL },
		{ "/translation() * a vector doesn't change it", matrix_transform_test3, NULL, NULL, 0, NULL },
		{ "/scaling() scales a point", matrix_transform_test4, NULL, NULL, 0, NULL },
		{ "/scaling() scales a vector", matrix_transform_test5, NULL, NULL, 0, NULL },
		{ "/inverse(scaling()) inverts the scaling", matrix_transform_test6, NULL, NULL, 0, NULL },
		{ "/rotation_x()", matrix_transform_test7, NULL, NULL, 0, NULL },
		{ "/inverse(rotation_x())", matrix_transform_test8, NULL, NULL, 0, NULL },
		{ "/rotation_y()", matrix_transform_test9, NULL, NULL, 0, NULL },
		{ "/rotation_z()", matrix_transform_test10, NULL, NULL, 0, NULL },
		{ "/individual transformations", matrix_transform_test11, NULL, NULL, 0, NULL },
		{ "/chained transformations", matrix_transform_test12, NULL, NULL, 0, NULL },
		{ "/chained n transformations", matrix_transform_test13, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitTest ray_tests[] = {
		{ "/new_ray()", ray_test1, NULL, NULL, 0, NULL },
		{ "/position()", ray_test2, NULL, NULL, 0, NULL },
		{ "/a ray intersect() a sphere at two points", ray_test3, NULL, NULL, 0, NULL },
		{ "/a ray intersect() a sphere at a tangent", ray_test4, NULL, NULL, 0, NULL },
		{ "/a ray misses the sphere", ray_test5, NULL, NULL, 0, NULL },
		{ "/a ray originates inside a sphere", ray_test6, NULL, NULL, 0, NULL },
		{ "/a sphere is behind a ray", ray_test7, NULL, NULL, 0, NULL },
		{ "/an intersection encapsulates t and object", ray_test8, NULL, NULL, 0, NULL },
		{ "/intersect() sets the object on the intersection", ray_test9, NULL, NULL, 0, NULL },
		{ "/hit() when all inters are positive", ray_test10, NULL, NULL, 0, NULL },
		{ "/hit() when some are negative", ray_test11, NULL, NULL, 0, NULL },
		{ "/hit() when all inters are negative", ray_test12, NULL, NULL, 0, NULL },
		{ "/hit() with a scrambled order", ray_test13, NULL, NULL, 0, NULL },
		{ "/tranform() a ray with a translation matrix", ray_test14, NULL, NULL, 0, NULL },
		{ "/tranform() a ray with a scaling matrix", ray_test15, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitTest sphere_tests[] = {
		{ "/new_sphere() has a transform matrix", sphere_test1, NULL, NULL, 0, NULL },
		{ "/set_transform() sets a new sphere transform matrix", sphere_test2, NULL, NULL, 0, NULL },
		{ "/intersect() uses the sphere transform matrix", sphere_test2, NULL, NULL, 0, NULL },
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

	MunitSuite ray_suite = {
		"/rays",
		ray_tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	MunitSuite sphere_suite = {
		"/shperes",
		sphere_tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	MunitSuite suites[] = {
		tuple_suite,
		matrix_suite,
		matrix_transform_suite,
		ray_suite,
		sphere_suite,
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
