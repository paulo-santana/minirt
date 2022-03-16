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

typedef struct s_computations {
	float			t;
	void			*object;
	t_object_types	object_type;
	t_tuple			*point;
	t_tuple			*eyev;
	t_tuple			*normalv;
	int				inside;
}	t_computations;

t_computations *prepare_computations(t_intersection *intersection, t_ray *ray)
{
	t_computations	*comps;
	t_tuple			*tmp;

	comps = malloc(sizeof(t_computations));
	comps->t = intersection->t;
	comps->object = intersection->object;
	comps->point = get_position(ray, intersection->t);
	comps->eyev = negate_tuple(ray->direction);
	comps->normalv = normal_at(comps->object, comps->point);
	comps->inside = 0;
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = 1;
		tmp = comps->normalv;
		comps->normalv = negate_tuple(comps->normalv);
		free(tmp);
	}
	return (comps);
}

// intersect a world with a ray
MunitResult world_test4(const MunitParameter params[], void *fixture)
{
	t_ray *ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_sphere *sphere = new_sphere();
	t_intersection *i = new_intersection(4, sphere, OBJ_SPHERE);

	t_computations *comps = prepare_computations(i, ray);

	t_tuple *expected_point = new_point(0, 0, -1);
	t_tuple *expected_eyev = new_vector(0, 0, -1);
	t_tuple *expected_normalv = new_vector(0, 0, -1);

	munit_assert_float(comps->t, ==, i->t);
	munit_assert_ptr_equal(comps->object, i->object);
	munit_assert_true(tuple_equals(comps->point, expected_point));
	munit_assert_true(tuple_equals(comps->eyev, expected_eyev));
	munit_assert_true(tuple_equals(comps->normalv, expected_normalv));
	return (MUNIT_OK);
}

// the hit, when an intersection occurs on the outside
MunitResult world_test5(const MunitParameter params[], void *fixture)
{
	t_ray *ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	t_sphere *sphere = new_sphere();
	t_intersection *i = new_intersection(4, sphere, OBJ_SPHERE);
	t_computations *comps = prepare_computations(i, ray);

	munit_assert_true(comps->inside == 0);
	return (MUNIT_OK);
}

// the hit, when an intersection occurs on the inside
MunitResult world_test6(const MunitParameter params[], void *fixture)
{
	t_ray *ray = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	t_sphere *sphere = new_sphere();
	t_intersection *i = new_intersection(1, sphere, OBJ_SPHERE);
	t_computations *comps = prepare_computations(i, ray);

	t_tuple *expected_normalv = new_vector(0, 0, -1);

	munit_assert_true(comps->inside == 1);
	munit_assert_true(tuple_equals(comps->normalv, expected_normalv));
	return (MUNIT_OK);
}
