#include "lights/lights.h"
#include "matrix/matrix.h"
#include "munit/munit.h"
#include "../src/structures.h"
#include "../src/minirt.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
#include "tuple/tuple.h"
#include "../libft/libft.h"
#include "utils.h"
#include <math.h>

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
	munit_assert_true(world->objects.total == 0);
	munit_assert_true(world->objects.sphere_count == 0);
	return (MUNIT_OK);
}

void	add_sphere(t_world *world, t_sphere *sphere)
{
	ft_lstadd_front(&world->objects.spheres, ft_lstnew(sphere));
	world->objects.total++;
	world->objects.sphere_count++;
}

t_world *default_world(void)
{
	t_world		*world;
	t_sphere	*s1;
	t_sphere	*s2;
	t_matrix	*scale;

	world = new_world();
	if (world == NULL)
		return (NULL);
	world->light = new_point_light(
		new_point(-10, 10, -10),
		new_color(1, 1, 1)
	);
	s1 = new_sphere();
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	free(s1->material->color);
	s1->material->color = new_color(0.8, 1.0, 0.6);
	s2 = new_sphere();
	scale = scaling(0.5, 0.5, 0.5);
	set_transform(s2, scale);
	add_sphere(world, s1);
	add_sphere(world, s2);
	return (world);
}

// the default world
// NOTE: this will have to change
MunitResult world_test2(const MunitParameter params[], void *fixture)
{
	t_point_light *light = new_point_light(
			new_point(-10, 10, -10),
			new_color(1, 1, 1)
		);
	t_sphere *s1 = new_sphere();
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	free(s1->material->color);
	s1->material->color = new_color(0.8, 1.0, 0.6);

	t_sphere *s2 = new_sphere();
	t_matrix *t = scaling(0.5, 0.5, 0.5);
	set_transform(s2, t);
	t_world	*world = default_world();

	t_world *expected = new_world();
	expected->light = light;
	add_sphere(expected, s1);
	add_sphere(expected, s2);

	munit_assert_true(world_equals(expected, world));
	munit_assert_true(world->objects.total == 2);
	munit_assert_true(world->objects.sphere_count == 2);
	return (MUNIT_OK);
}

t_intersections *intersect_world(t_world *world, t_ray *ray)
{
	t_intersections	*xs;
	t_list			*spheres;

	xs = new_intersections_list();
	spheres = world->objects.spheres;
	while (spheres)
	{
		intersect(xs, spheres->content, ray);
		spheres = spheres->next;
	}
	sort_intersections(xs);
	return (xs);
}

// intersect a world with a ray
MunitResult world_test3(const MunitParameter params[], void *fixture)
{
	t_world *w = default_world();
	t_ray *ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));

	t_intersections *xs = intersect_world(w, ray);

	munit_assert_int(xs->count, ==, 4);
	munit_assert_float(xs->intersections[0]->t, ==, 4);
	munit_assert_float(xs->intersections[1]->t, ==, 4.5);
	munit_assert_float(xs->intersections[2]->t, ==, 5.5);
	munit_assert_float(xs->intersections[3]->t, ==, 6);
	return (MUNIT_OK);
}
