#include "matrix/matrix.h"
#include "munit/munit.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "ray/ray.h"
#include <stdlib.h>

MunitResult sphere_test1(const MunitParameter params[], void *fixture)
{
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	t_matrix *identity = identity_matrix();

	munit_assert_true(matrix_equals(sphere->transform, identity));
	free(identity);
	destroy_sphere(sphere);
	return (MUNIT_OK);
}
