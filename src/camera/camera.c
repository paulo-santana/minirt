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
#include "structures.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

t_camera	*new_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	*camera;
	double		half_view;
	double		aspect;

	camera = malloc(sizeof(t_camera));
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = field_of_view;
	camera->transform = identity_matrix();
	camera->inverse_transform = identity_matrix();
	half_view = tanf(field_of_view / 2);
	aspect = (double)hsize / vsize;
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

void	set_camera_transform(t_camera *camera, t_matrix *t)
{
	free(camera->transform);
	camera->transform = t;
	free(camera->inverse_transform);
	camera->inverse_transform = inverse(t);
}

t_ray	*generate_ray(t_camera *camera, t_tuple *pixel)
{
	t_tuple	*origin;
	t_tuple	*direction;
	t_tuple	*center;
	t_tuple	*tmp;

	center = new_point(0, 0, 0);
	origin = matrix_multiply_tuple(camera->inverse_transform, center);
	tmp = subtract_tuples(pixel, origin);
	direction = normalize(tmp);
	free(tmp);
	free(center);
	return (new_ray(origin, direction));
}

t_ray	*ray_to_pixel(int x, int y, t_camera *camera)
{
	double	offset[2];
	double	world[2];
	t_ray	*ray;
	t_tuple	*pixel;
	t_tuple	*point;

	offset[X] = (x + 0.5) * camera->pixel_size;
	offset[Y] = (y + 0.5) * camera->pixel_size;
	world[X] = camera->half_width - offset[X];
	world[Y] = camera->half_height - offset[Y];
	point = new_point(world[X], world[Y], -1);
	pixel = matrix_multiply_tuple(camera->inverse_transform, point);
	ray = generate_ray(camera, pixel);
	free(point);
	free(pixel);
	return (ray);
}

void	destroy_camera(t_camera *camera)
{
	free(camera->transform);
	free(camera->inverse_transform);
	free(camera);
}
