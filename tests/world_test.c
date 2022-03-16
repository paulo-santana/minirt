#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "tuple/tuple.h"
#include "../libft/libft.h"
#include <math.h>

typedef struct s_objects {
	int		count;
	t_list	*items;
} t_objects;

typedef struct s_world {
	t_point_light	*light;
	t_objects		objects;
} t_world;

t_world	*new_world(void)
{
	t_world	*world;

	world = ft_calloc(1, sizeof(t_world));
	return (world);
}

// creating a world
MunitResult world_test1(const MunitParameter params[], void *fixture)
{
	t_world	*world = new_world();

	munit_assert_true(world->light == NULL);
	munit_assert_true(world->objects.count == 0);
	return (MUNIT_OK);
}
