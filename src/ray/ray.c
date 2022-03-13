/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:15:01 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/13 13:32:34 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "tuple/tuple.h"

t_tuple	*position(t_ray *ray, float t)
{
	t_tuple	*distance;
	t_tuple	*new_pos;

	distance = multiply_scalar(ray->direction, t);
	new_pos = add_tuples(ray->origin, distance);
	free(distance);
	return (new_pos);
}

t_intersections	*intersect(t_sphere *sphere, t_ray *ray)
{
	float			abc[3];
	float			discriminant;
	t_intersections	*inter;
	t_tuple			*sphere_to_ray;

	sphere_to_ray = subtract_tuples(ray->origin, sphere->position);
	abc[0] = dot(ray->direction, ray->direction);
	abc[1] = 2 * dot(ray->direction, sphere_to_ray);
	abc[2] = dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	inter = malloc(sizeof(t_intersections));
	inter->count = 0;
	inter->distances = NULL;
	if (discriminant < 0)
		return (inter);
	inter->distances = malloc(sizeof(float) * 2);
	inter->distances[0] = (-abc[1] - sqrtf(discriminant)) / (2 * abc[0]);
	inter->distances[1] = (-abc[1] + sqrtf(discriminant)) / (2 * abc[0]);
	inter->count = 2;
	return (inter);
}
