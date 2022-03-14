/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:45:23 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/13 15:45:23 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <libft.h>
#include <stdlib.h>
#include "tuple/tuple.h"
#include "utils/utils.h"

void	add_intersection(t_intersections *intersections, t_intersection *new)
{
	t_intersection	**arr;

	if (intersections->count >= intersections->size)
	{
		arr = malloc(sizeof(t_intersection **) * intersections->size + 50);
		ft_memmove(arr, intersections->intersections, sizeof(t_intersection *)
			* intersections->size + 50);
		free(intersections->intersections);
		intersections->intersections = arr;
	}
	intersections->intersections[intersections->count] = new;
	intersections->count++;
}

void	intersect(
		t_intersections *intersections, t_sphere *sphere, t_ray *ray)
{
	float			abc[3];
	float			discriminant;
	float			result;
	t_intersection	*inter;
	t_tuple			*sphere_to_ray;

	sphere_to_ray = subtract_tuples(ray->origin, sphere->position);
	abc[0] = dot(ray->direction, ray->direction);
	abc[1] = 2 * dot(ray->direction, sphere_to_ray);
	abc[2] = dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (discriminant < 0)
		return (free(sphere_to_ray));
	result = (-abc[1] - sqrtf(discriminant)) / (2 * abc[0]);
	inter = new_intersection(result, sphere, OBJ_SPHERE);
	add_intersection(intersections, inter);
	if (fequals(discriminant, 0))
		return (free(sphere_to_ray));
	result = (-abc[1] + sqrtf(discriminant)) / (2 * abc[0]);
	inter = new_intersection(result, sphere, OBJ_SPHERE);
	add_intersection(intersections, inter);
	return (free(sphere_to_ray));
}

t_intersection	*new_intersection(float t, void *obj, t_object_types obj_type)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
	i->t = t;
	i->object = obj;
	i->object_type = obj_type;
	return (i);
}

t_intersection	**intersection_arr(t_list *list)
{
	int				i;
	int				size;
	t_intersection	**inters;

	size = ft_lstsize(list);
	inters = malloc(sizeof(t_intersection *) * size);
	i = 0;
	while (list)
	{
		inters[i] = list->content;
		list = list->next;
	}
	return (inters);
}
