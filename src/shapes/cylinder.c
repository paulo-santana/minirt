/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:49:28 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/11 22:51:02 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "ray/ray.h"

void	cylinder_intersect(t_shape *cylinder, t_ray *ray, t_intersections *xs)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	result;

	a = pow(ray->direction->x, 2) + pow(ray->direction->z, 2);
	if (dequals(a, 0))
		return ;
	b = 2 * ray->origin->x * ray->direction->x
		+ 2 * ray->origin->z * ray->direction->z;
	c = pow(ray->origin->x, 2) + pow(ray->origin->z, 2) - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	result = (-b - sqrt(discriminant)) / (2 * a);
	add_intersection(xs, new_intersection(result, cylinder, OBJ_CYLINDER));
	result = (-b + sqrt(discriminant)) / (2 * a);
	add_intersection(xs, new_intersection(result, cylinder, OBJ_CYLINDER));
}

t_tuple	*cylinder_normal_at(t_shape *cylinder, t_tuple *point)
{
	(void)cylinder;
	return (new_vector(point->x, 0, point->z));
}

void	destroy_cylinder(t_shape *cyl)
{
	free(cyl->transform);
	free(cyl->inverse_transform);
	destroy_material(cyl->material);
}

t_shape	*new_cylinder(void)
{
	t_shape	*cylinder;

	cylinder = new_shape();
	cylinder->cylinder_props.radius = 1;
	cylinder->cylinder_props.position.w = 1;
	cylinder->intersect = cylinder_intersect;
	cylinder->normal_at = cylinder_normal_at;
	cylinder->destroy_fn = destroy_cylinder;
	return (cylinder);
}
