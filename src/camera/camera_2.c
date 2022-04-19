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
	t_matrix	*rot;
	t_tuple		*tmp;
	t_tuple		*result;

	if (dequals(fabs(orientation->x), 1))
		return (new_vector(0, 1, 0));
	rot = rotation_x(M_PI_2);
	tmp = matrix_multiply_tuple(rot, orientation);
	if (tmp->y < 0)
	{
		result = negate_tuple(tmp);
		free(tmp);
	}
	else
		result = tmp;
	free(rot);
	return (result);
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
	transform = view_transform(
			from,
			orientation,
			up);
	set_camera_transform(camera, transform);
	free(from);
	free(up);
	return (camera);
}
