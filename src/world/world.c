#include "world.h"
#include "libft.h"
#include "lights/lights.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "shapes/shapes.h"

t_world	*new_world(void)
{
	t_world	*world;

	world = ft_calloc(1, sizeof(t_world));
	return (world);
}

void	add_sphere(t_world *world, t_sphere *sphere)
{
	ft_lstadd_back(&world->objects.spheres, ft_lstnew(sphere));
	world->objects.total++;
	world->objects.sphere_count++;
}

void	add_light(t_world *world, t_point_light *light)
{
	ft_lstadd_back(&world->lights, ft_lstnew(light));
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
	add_light(world, new_point_light(new_point(-10, 10, -10), new_color(1, 1, 1)));
	// add_light(world, new_point_light(new_point(-10, -5, -10), new_color(1, .1, .1)));
	s1 = new_sphere();
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	s1->material->shininess = 200;
	free(s1->material->color);
	s1->material->color = new_color(0.8, 1.0, 0.6);
	s2 = new_sphere();
	scale = scaling(0.5, 0.5, 0.5);
	set_transform(s2, scale);
	add_sphere(world, s1);
	add_sphere(world, s2);
	return (world);
}

void	destroy_world(t_world *world)
{
	// if (world->light)
	ft_lstclear(&world->lights, (void(*)(void*))destroy_point_light);
	ft_lstclear(&world->objects.spheres, destroy_sphere);
	free(world);
}
