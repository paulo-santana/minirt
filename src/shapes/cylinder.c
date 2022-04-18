/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:49:28 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/15 23:29:27 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "ray/ray.h"
#include "structures.h"
#include "tuple/tuple.h"

static void	swap_if_needed(double *t0, double *t1)
{
	double	tmp;

	if (*t0 > *t1)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
}

static void	add_if_intersect(
		t_intersections *xs, double t[2], t_shape *cyl, t_ray *ray)
{
	double	y;
	double	min;
	double	max;

	swap_if_needed(&t[0], &t[1]);
	min = cyl->cylinder_props.min;
	max = cyl->cylinder_props.max;
	y = ray->origin->y + t[0] * ray->direction->y;
	if (min < y && y < max)
		add_intersection(xs, new_intersection(t[0], cyl, OBJ_CYLINDER));
	y = ray->origin->y + t[1] * ray->direction->y;
	if (min < y && y < max)
		add_intersection(xs, new_intersection(t[1], cyl, OBJ_CYLINDER));
}

void	cylinder_intersect(t_shape *cylinder, t_ray *ray, t_intersections *xs)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t[2];

	intersect_caps(cylinder, ray, xs);
	a = pow(ray->direction->x, 2) + pow(ray->direction->z, 2);
	if (dequals(a, 0))
		return ;
	b = 2 * ray->origin->x * ray->direction->x
		+ 2 * ray->origin->z * ray->direction->z;
	c = pow(ray->origin->x, 2) + pow(ray->origin->z, 2) - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	add_if_intersect(xs, t, cylinder, ray);
}

t_tuple	*cylinder_normal_at(t_shape *cylinder, t_tuple *point)
{
	double	dist;

	dist = (point->x * point->x) + (point->z * point->z);
	if (dist < 1 && point->y >= cylinder->cylinder_props.max - EPSILON)
		return (new_vector(0, 1, 0));
	else if (dist < 1 && point->y <= cylinder->cylinder_props.min + EPSILON)
		return (new_vector(0, -1, 0));
	return (new_vector(point->x, 0, point->z));
}

void	destroy_cylinder(t_shape *cyl)
{
	free(cyl->transform);
	free(cyl->inverse_transform);
	destroy_material(cyl->material);
	free(cyl);
}

t_shape	*new_cylinder(void)
{
	t_shape	*cylinder;

	cylinder = new_shape();
	cylinder->cylinder_props.radius = 1;
	cylinder->cylinder_props.position.w = 1;
	cylinder->cylinder_props.min = 1;
	cylinder->cylinder_props.max = 2;
	cylinder->intersect = cylinder_intersect;
	cylinder->normal_at = cylinder_normal_at;
	cylinder->destroy_fn = destroy_cylinder;
	return (cylinder);
}
