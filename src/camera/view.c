/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:08:37 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/17 12:13:18 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "structures.h"

void	set_camera_dimensions(t_camera *camera, t_canvas *canvas)
{
	double	half_view;
	double	aspect;

	camera->hsize = canvas->width;
	camera->vsize = canvas->height;
	half_view = tan(camera->fov / 2);
	aspect = (double)camera->hsize / camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = camera->half_width * 2 / camera->hsize;
}

t_matrix	*translate_view(t_matrix *orientation, t_tuple *from)
{
	t_matrix	*result;
	t_matrix	*t;

	t = translation(-from->x, -from->y, -from->z);
	result = matrix_multiply(orientation, t);
	free(t);
	return (result);
}

t_matrix	*view_transform(t_tuple *from, t_tuple *to, t_tuple *up)
{
	void		*result;
	t_tuple		*forward;
	t_tuple		*left;
	t_tuple		*true_up;
	t_matrix	*orientation;

	result = subtract_tuples(to, from);
	forward = normalize(result);
	free(result);
	up = normalize(up);
	left = cross(forward, up);
	true_up = cross(left, forward);
	free(up);
	orientation = new_matrix(4, (double [4][4]){
		{left->x, left->y, left->z, 0},
		{true_up->x, true_up->y, true_up->z, 0},
		{-forward->x, -forward->y, -forward->z, 0},
		{0, 0, 0, 1},
		});
	result = translate_view(orientation, from);
	free(orientation);
	free(true_up);
	free(left);
	free(forward);
	return (result);
}
