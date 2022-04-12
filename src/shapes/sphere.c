/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:04:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/11 22:04:35 by psergio-         ###   ########.fr       */
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

void	destroy_sphere(t_shape *sphere)
{
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

double	get_discriminant(t_sphere *sphere, t_ray *ray, double abc[3])
{
	t_tuple		*sphere_to_ray;

	sphere_to_ray = subtract_tuples(ray->origin, &sphere->position);
	abc[0] = dot(ray->direction, ray->direction);
	abc[1] = 2 * dot(ray->direction, sphere_to_ray);
	abc[2] = dot(sphere_to_ray, sphere_to_ray) - 1;
	free(sphere_to_ray);
	return ((abc[1] * abc[1]) - (4 * abc[0] * abc[2]));
}

void	sphere_intersect(
		t_shape *sphere, t_ray *ray, t_intersections *intersections)
{
	double			abc[3];
	double			discriminant;
	double			result;

	discriminant = get_discriminant(&sphere->sphere_props, ray, abc);
	if (discriminant < 0)
		return ;
	result = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	add_intersection(intersections,
		new_intersection(result, sphere, OBJ_SPHERE));
	if (dequals(discriminant, 0))
		return ;
	result = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	add_intersection(intersections,
		new_intersection(result, sphere, OBJ_SPHERE));
	return ;
}
