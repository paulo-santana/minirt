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

#include "matrix/matrix.h"
#include "ray.h"
#include <libft.h>
#include <stdlib.h>
#include "structures.h"
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
	intersections->is_sorted = 0;
}

float	get_discriminant(t_sphere *sphere, t_ray *ray, float abc[3])
{
	t_tuple		*sphere_to_ray;

	sphere_to_ray = subtract_tuples(ray->origin, sphere->position);
	abc[0] = dot(ray->direction, ray->direction);
	abc[1] = 2 * dot(ray->direction, sphere_to_ray);
	abc[2] = dot(sphere_to_ray, sphere_to_ray) - 1;
	free(sphere_to_ray);
	return ((abc[1] * abc[1]) - (4 * abc[0] * abc[2]));
}

void	intersect(
		t_intersections *intersections, t_sphere *sphere, t_ray *ray)
{
	float			abc[3];
	float			discriminant;
	float			result;
	t_ray			*transformed_ray;
	t_matrix		*sphere_transform;

	sphere_transform = inverse(sphere->transform);
	transformed_ray = transform(ray, sphere_transform);
	discriminant = get_discriminant(sphere, transformed_ray, abc);
	destroy_ray(transformed_ray);
	free(sphere_transform);
	if (discriminant < 0)
		return ;
	result = (-abc[1] - sqrtf(discriminant)) / (2 * abc[0]);
	add_intersection(intersections,
		new_intersection(result, sphere, OBJ_SPHERE));
	if (fequals(discriminant, 0))
		return ;
	result = (-abc[1] + sqrtf(discriminant)) / (2 * abc[0]);
	add_intersection(intersections,
		new_intersection(result, sphere, OBJ_SPHERE));
	return ;
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

void	sort_intersections(t_intersections *inters)
{
	int				i;
	int				j;
	t_intersection	*tmp;

	if (inters->is_sorted)
		return ;
	i = 0;
	while (i < inters->count)
	{
		j = i;
		while (j < inters->count)
		{
			if (inters->intersections[i]->t > inters->intersections[j]->t)
			{
				tmp = inters->intersections[i];
				inters->intersections[i] = inters->intersections[j];
				inters->intersections[j] = tmp;
			}
			j++;
		}
		i++;
	}
	inters->is_sorted = 1;
}

t_intersection	*hit(t_intersections *inters)
{
	int				i;

	if (!inters->is_sorted)
		sort_intersections(inters);
	i = 0;
	while (i < inters->count)
	{
		if (inters->intersections[i]->t > 0)
			return (inters->intersections[i]);
		i++;
	}
	return (NULL);
}

t_intersections *new_intersections_list(void)
{
	t_intersections	*intersections;

	intersections = malloc(sizeof(t_intersections));
	intersections->count = 0;
	intersections->size = 50;
	intersections->is_sorted = 0;
	intersections->intersections = malloc(sizeof(t_intersection *) * 50);
	return (intersections);
}

void	destroy_intersections_list(t_intersections *inters)
{
	while (inters->count--)
		free(inters->intersections[inters->count]);
	free(inters->intersections);
	free(inters);
}
