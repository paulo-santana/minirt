#include "matrix/matrix.h"
#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "../src/debug.h"
#include "tuple/tuple.h"
#include "camera/camera.h"
#include <math.h>

// the pixel size for a horizontal canvas
MunitResult camera_test1(const MunitParameter params[], void *fixture)
{
	t_camera *camera = new_camera(200, 125, M_PI_2);

	munit_assert_float(camera->pixel_size, ==, 0.01);

	return (MUNIT_OK);
}

// the pixel size for a vertical canvas
MunitResult camera_test2(const MunitParameter params[], void *fixture)
{
	t_camera *camera = new_camera(125, 200, M_PI_2);

	munit_assert_float(camera->pixel_size, ==, 0.01);

	return (MUNIT_OK);
}
