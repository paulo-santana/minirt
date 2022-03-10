#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"

MunitResult a_tuple_with_w_1_is_a_point(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(4.3, -4.2, 3.1, 1);

	munit_assert_float(a->x, ==, 4.3);
	munit_assert_float(a->y, ==, -4.2);
	munit_assert_float(a->z, ==, 3.1);
	munit_assert_float(a->w, ==, 1.0);
	munit_assert_true(is_point(a));
	munit_assert_false(is_vector(a));
	free(a);
	return (MUNIT_OK);
}

MunitResult a_tuple_with_w_0_is_a_vector(const MunitParameter params[], void *fixture)
{
	t_tuple *a = new_tuple(4.3, -4.2, 3.1, 0);

	munit_assert_float(a->x, ==, 4.3);
	munit_assert_float(a->y, ==, -4.2);
	munit_assert_float(a->z, ==, 3.1);
	munit_assert_float(a->w, ==, 0.0);
	munit_assert_false(is_point(a));
	munit_assert_true(is_vector(a));
	free(a);
	return (MUNIT_OK);
}

int main(int argc, char **argv) {
	MunitTest tests[] = {
		{ "/a tuple with w=1.0 is a point", a_tuple_with_w_1_is_a_point, NULL, NULL, 0, NULL },
		{ "/a tuple with w=0.0 is a vector", a_tuple_with_w_0_is_a_vector, NULL, NULL, 0, NULL },
		{ NULL, NULL, NULL, NULL, 0, NULL },
	};

	MunitSuite suite = {
		"/tuple",
		tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	return (munit_suite_main(&suite, NULL, argc, argv));
}
