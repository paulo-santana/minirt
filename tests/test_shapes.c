#include "matrix/matrix.h"
#include "munit/munit.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "ray/ray.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

t_shape *new_test_shape(void)
{
	t_shape *shape = new_shape();
	return (shape);
}

void destroy_shape(void *data)
{
	t_shape	*shape;

	shape = data;
	free(shape->transform);
	free(shape->inverse_transform);
	destroy_material(shape->material);
	free(shape);
}

// the default transformation
MunitResult shape_test1(const MunitParameter params[], void *fixture)
{
	t_shape *shape = new_test_shape();

	t_matrix *identity = identity_matrix();
	munit_assert_true(matrix_equals(shape->transform, identity));
	destroy_shape(shape);
	free(identity);
	return MUNIT_OK;
}

// assigning a transformation
MunitResult shape_test2(const MunitParameter params[], void *fixture)
{
	t_shape *shape = new_test_shape();

	t_matrix *t = translation(2, 3, 4);
	set_transform(shape, t);
	munit_assert_true(matrix_equals(shape->transform, t));
	destroy_shape(shape);
	return MUNIT_OK;
}

// the default material
MunitResult shape_test3(const MunitParameter params[], void *fixture)
{
	t_shape *shape = new_test_shape();

	t_matrix *t = translation(2, 3, 4);
	set_transform(shape, t);
	munit_assert_true(matrix_equals(shape->transform, t));
	destroy_shape(shape);
	return MUNIT_OK;
}
