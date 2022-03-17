/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:43:35 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/17 12:48:12 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera	*new_camera(int hsize, int vsize, float field_of_view)
{
	t_camera	*camera;
	float		half_view;
	float		aspect;

	camera = malloc(sizeof(t_camera));
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = field_of_view;
	camera->transform = identity_matrix();
	half_view = tanf(field_of_view / 2);
	aspect = (float)hsize / vsize;
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
	camera->pixel_size = camera->half_width * 2 / hsize;
	return (camera);
}
