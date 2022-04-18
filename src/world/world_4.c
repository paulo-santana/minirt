/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 01:27:58 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/18 01:40:43 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "world.h"
#include "libft.h"
#include "lights/lights.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "shapes/shapes.h"
#include "../matrix/matrix.h"

t_matrix	*get_orientation_matrix(double vector[3])
{
	double		xy_length;
	double		z_angle;
	double		x_angle;
	t_matrix	*rot_angles[3];
	t_matrix	*rot;

	xy_length = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	if (xy_length == 0)
		z_angle = M_PI_2;
	else
		z_angle = acos(vector[1] / xy_length);
	x_angle = acos(xy_length);
	rot_angles[0] = rotation_x(x_angle);
	rot_angles[1] = rotation_z(z_angle);
	rot_angles[2] = NULL;
	rot = matrix_multiply_n(rot_angles);
	free(rot_angles[0]);
	free(rot_angles[1]);
	return (rot);
}

void	set_cylinder_props_position(t_shape *shape, t_scene_object_param *obj)
{
	t_matrix	*translate;
	t_matrix	*rot;
	t_matrix	*scale;
	t_matrix	*transform;

	translate = translation(
			obj->cordinates[0],
			obj->cordinates[1],
			obj->cordinates[2]);
	rot = get_orientation_matrix(obj->orientation_vector);
	scale = scaling(obj->diameter / 2, 1, obj->diameter / 2);
	transform = matrix_multiply3(scale, rot, translate);
	set_transform(shape, transform);
	free(scale);
	free(rot);
	free(translate);
	shape->cylinder_props.max = obj->height * 0.5;
	shape->cylinder_props.min = -obj->height * 0.5;
	shape->cylinder_props.radius = obj->diameter * 0.5;
}

void	set_plane_props_position(t_shape *shape, t_scene_object_param *obj)
{
	t_matrix	*translate;
	t_matrix	*rot;
	t_matrix	*transform;

	translate = translation(
			obj->cordinates[0],
			obj->cordinates[1],
			obj->cordinates[2]);
	rot = get_orientation_matrix(obj->orientation_vector);
	transform = matrix_multiply(translate, rot);
	set_transform(shape, transform);
	free(translate);
	free(rot);
}

void	set_sphere_props_position(t_shape *shape, t_scene_object_param *obj)
{
	double		x;
	double		y;
	double		z;
	t_matrix	*transl;
	t_matrix	*scale;

	x = obj->cordinates[0];
	y = obj->cordinates[1];
	z = obj->cordinates[2];
	transl = translation(x, y, z);
	scale = scaling(obj->diameter / 2, obj->diameter / 2, obj->diameter / 2);
	set_transform(shape, matrix_multiply(transl, scale));
	free(transl);
	free(scale);
	shape->sphere_props.radius = obj->diameter * 0.5;
}
