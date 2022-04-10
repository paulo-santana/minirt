/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:04:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 16:25:35 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"
#include "shapes.h"
#include "structures.h"

t_tuple	*sphere_normal_at(t_shape *shape, t_tuple *point);

t_shape	*new_sphere(void)
{
	t_shape	*sphere;

	sphere = new_shape();
	sphere->sphere_props.position = (t_tuple){0, 0, 0, 1};
	sphere->sphere_props.radius = 1;
	sphere->intersect = sphere_intersect;
	sphere->normal_at = sphere_normal_at;
	sphere->destroy_fn = destroy_sphere;
	return (sphere);
}

void	destroy_sphere(void *data)
{
	t_shape	*sphere;

	sphere = data;
	free(sphere->transform);
	free(sphere->inverse_transform);
	destroy_material(sphere->material);
	free(sphere);
}

t_tuple	*sphere_normal_at(t_shape *shape, t_tuple *point)
{
	t_tuple		*object_normal;
	t_tuple		*tmp;

	tmp = new_point(0, 0, 0);
	object_normal = subtract_tuples(point, tmp);
	free(tmp);
	object_normal->w = 0;
	(void)shape;
	return (object_normal);
}
