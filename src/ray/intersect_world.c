/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:16:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/16 01:40:07 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lights/lights.h"
#include "ray.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "utils/utils.h"

#ifndef EPSILON
# define EPSILON .0001

#endif /* !EPSILON */

t_computations	*prepare_computations(t_intersection *intersection, t_ray *ray)
{
	t_computations	*comps;
	t_tuple			*tmp;

	comps = malloc(sizeof(t_computations));
	comps->t = intersection->t;
	comps->object = intersection->object;
	comps->point = get_position(ray, comps->t);
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
	tmp = multiply_scalar(comps->normalv, EPSILON);
	comps->over_point = add_tuples(comps->point, tmp);
	free(tmp);
	return (comps);
}

void	intersect(t_shape *shape, t_ray *ray, t_intersections *xs)
{
	t_ray	*local_ray;

	local_ray = transform(ray, shape->inverse_transform);
	shape->intersect(shape, local_ray, xs);
	destroy_ray(local_ray);
}

t_intersections	*intersect_world(t_world *world, t_ray *ray)
{
	t_intersections	*xs;
	t_list			*object;
	t_shape			*shape;

	xs = new_intersections_list();
	object = world->objects.spheres;
	while (object)
	{
		shape = object->content;
		intersect(shape, ray, xs);
		object = object->next;
	}
	sort_intersections(xs);
	return (xs);
}

t_color	*sum_color_list(t_list *colors)
{
	t_color	*result;
	t_color	*tmp;

	result = new_color(0, 0, 0);
	while (colors)
	{
		tmp = result;
		result = add_colors(result, colors->content);
		free(tmp);
		colors = colors->next;
	}
	return (result);
}

static t_ray	*ray_from_to(t_tuple *origin, t_tuple *target)
{
	t_tuple			*v;
	t_tuple			*direction;
	t_ray			*ray;

	v = subtract_tuples(target, origin);
	direction = normalize(v);
	ray = new_ray(origin, direction);
	free(v);
	return (ray);
}

int	is_shadowed(t_world *world, t_tuple *point, t_point_light *light)
{
	t_tuple			*v;
	double			distance;
	t_intersections	*xs;
	int				result;
	t_ray			*ray;

	v = subtract_tuples(light->position, point);
	distance = magnitude(v);
	ray = ray_from_to(point, light->position);
	xs = intersect_world(world, ray);
	result = (hit(xs) != NULL && hit(xs)->t < distance);
	ray->origin = NULL;
	destroy_ray(ray);
	free(v);
	destroy_intersections_list(xs);
	return (result);
}

t_color	*shade_hit(t_world *world, t_computations *comps)
{
	t_lighting_args	args;
	t_list			*light;
	t_list			*colors;
	t_color			*final_color;

	light = world->lights;
	args.material = comps->object->material;
	args.position = comps->over_point;
	args.eye_vector = comps->eyev;
	args.normal_vector = comps->normalv;
	colors = NULL;
	ft_lstadd_front(&colors, ft_lstnew(get_ambient(&args)));
	while (light)
	{
		args.light = light->content;
		args.in_shadow = is_shadowed(world, comps->over_point, light->content);
		ft_lstadd_front(&colors, ft_lstnew(lighting(&args)));
		light = light->next;
	}
	final_color = sum_color_list(colors);
	ft_lstclear(&colors, free);
	return (final_color);
}

void	destroy_computations(t_computations *comps)
{
	free(comps->eyev);
	free(comps->normalv);
	free(comps->point);
	free(comps);
}

t_color	*color_at(t_world *world, t_ray *ray)
{
	t_computations	*comps;
	t_intersection	*intersection;
	t_intersections	*xs;
	t_color			*color;

	xs = intersect_world(world, ray);
	intersection = hit(xs);
	if (intersection == NULL)
	{
		destroy_intersections_list(xs);
		return (new_color(0, 0, 0));
	}
	comps = prepare_computations(intersection, ray);
	color = shade_hit(world, comps);
	destroy_intersections_list(xs);
	free(comps->eyev);
	free(comps->normalv);
	free(comps->point);
	free(comps->over_point);
	free(comps);
	return (color);
}
