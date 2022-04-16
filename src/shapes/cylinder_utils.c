/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 22:09:49 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/15 23:43:33 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"
#include "shapes.h"
#include "structures.h"

static int	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin->x + t * ray->direction->x;
	z = ray->origin->z + t * ray->direction->z;
	return ((x * x + z * z) <= 1);
}

void	intersect_caps(t_shape *shape, t_ray *ray, t_intersections *xs)
{
	double	t;

	if (dequals(ray->direction->y, 0))
		return ;
	t = (shape->cylinder_props.min - ray->origin->y) / ray->direction->y;
	if (check_cap(ray, t))
		add_intersection(xs, new_intersection(t, shape, OBJ_CYLINDER));
	t = (shape->cylinder_props.max - ray->origin->y) / ray->direction->y;
	if (check_cap(ray, t))
		add_intersection(xs, new_intersection(t, shape, OBJ_CYLINDER));
}
