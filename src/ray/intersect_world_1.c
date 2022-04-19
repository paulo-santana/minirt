/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:16:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/19 03:20:28 by fbafica          ###   ########.fr       */
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
