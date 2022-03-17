/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:16:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/16 17:56:41 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lights/lights.h"
#include "ray.h"
#include "structures.h"
#include "tuple/tuple.h"

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
	return (comps);
}

t_intersections	*intersect_world(t_world *world, t_ray *ray)
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

t_color	*shade_hit(t_world *world, t_computations *comps)
{
	t_lighting_args	args;
	t_list			*light;
	t_list			*colors;

	light = world->lights;
	colors = NULL;
	while (light)
	{
		args.material = ((t_sphere *)comps->object)->material;
		args.light = light->content;
		args.position = comps->point;
		args.eye_vector = comps->eyev;
		args.normal_vector = comps->normalv;
		light = light->next;
		ft_lstadd_front(&colors, ft_lstnew(lighting(&args)));
	}
	return (sum_color_list(colors));
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
	free(comps);
	return (color);
}
