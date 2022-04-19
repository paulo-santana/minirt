/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:57:34 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 20:59:16 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"
#include "shapes.h"

void	destroy_plane(t_shape *shape)
{
	free(shape->transform);
	free(shape->inverse_transform);
	destroy_material(shape->material);
	free(shape);
}

void	plane_intersect(t_shape *shape, t_ray *ray, t_intersections *xs)
{
	double			t;
	t_intersection	*inter;

	if (fabs(ray->direction->y) < EPSILON)
		return ;
	t = -ray->origin->y / ray->direction->y;
	inter = new_intersection(t, shape, OBJ_PLANE);
	add_intersection(xs, inter);
}

t_tuple	*plane_normal_at(t_shape *shape, t_tuple *tuple)
{
	(void)shape;
	(void)tuple;
	return (new_vector(0, 1, 0));
}

t_shape	*new_plane(void)
{
	t_shape	*plane;

	plane = new_shape();
	plane->material->specular = .2;
	plane->destroy_fn = destroy_plane;
	plane->normal_at = plane_normal_at;
	plane->intersect = plane_intersect;
	return (plane);
}
