/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 03:11:48 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:20:34 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lights/lights.h"
#include "ray.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "utils/utils.h"

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
