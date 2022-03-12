#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
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
	t_tuple *p = new_vector(-4, 6, 8);
	t_tuple *expected = new_vector(-8, 18, 32);

	t_tuple *result = matrix_multiply_tuple(transform, p);
	munit_assert_true(tuple_equals(result, expected));
	return (MUNIT_OK);
}
