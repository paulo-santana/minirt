/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 02:51:25 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:00:28 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "matrix/matrix.h"
#include "structures.h"
#include "minirt.h"
#include "tuple/tuple.h"
#include <math.h>

t_tuple	*get_up(t_tuple *orientation)
{
	t_tuple	*right;
	t_tuple	*up;

	if (dequals(fabs(orientation->y), 1))
		return (new_vector(1, 0, 0));
	right = cross(&(t_tuple){0, 1, 0, 0}, orientation);
	up = cross(orientation, right);
	free(right);
	return (up);
}

t_camera	*get_camera_params(t_parameters *p)
{
	t_camera	*camera;
	t_tuple		*up;
	t_tuple		*orientation;
	t_tuple		*from;
	t_matrix	*transform;

	camera = new_camera(WIN_X, WIND_Y, p->c_fov);
	orientation = new_vector(
			p->c_orientation_vector[0],
			p->c_orientation_vector[1],
			p->c_orientation_vector[2]);
	from = new_point(p->c_view_point[0],
			p->c_view_point[1],
			p->c_view_point[2]);
	up = get_up(orientation);
	transform = view_transform(from, orientation, up);
	set_camera_transform(camera, transform);
	free(from);
	free(up);
	return (camera);
}
