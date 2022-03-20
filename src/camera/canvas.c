/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:37:16 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/17 19:33:00 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "debug.h"
#include "ray/ray.h"
#include "structures.h"
#include <stdio.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

t_canvas	*new_canvas(int width, int height)
{
	t_canvas	*canvas;
	int			size;

	canvas = malloc(sizeof(t_canvas));
	size = sizeof(canvas->data) * width * height;
	canvas->data = malloc(size);
	ft_bzero(canvas->data, size);
	canvas->width = width;
	canvas->height = height;
	return (canvas);
}

unsigned int	color_to_int(t_color *color)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = roundf(color->red * 255);
	green = roundf(color->green * 255);
	blue = roundf(color->blue * 255);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return (red << 16 | green << 8 | blue);
}

#define THREAD_NUM 6

typedef struct s_thread_args {
	int			start;
	int			end;
	t_canvas	*image;
	t_camera	*camera;
	t_world		*world;
}	t_thread_args;

void	*draw_piece(void *args)
{
	int				x;
	int				y;
	t_ray			*ray;
	t_color			*color;
	t_thread_args	*data;

	data = args;
	y = data->start;
	while (y < data->end)
	{
		x = 0;
		while (x < data->image->width)
		{
			ray = ray_to_pixel(x, y, data->camera);
			color = color_at(data->world, ray);
			destroy_ray(ray);
			data->image->data[y * data->image->width + x] = color_to_int(color);
			free(color);
			x++;
		}
		y++;
	}
	return (data);
}

t_canvas	*render(t_camera *camera, t_world *world)
{
	t_canvas		*image;
	int				piece_size;
	int				y;
	t_thread_args	args[THREAD_NUM];
	pthread_t		ids[THREAD_NUM];

	image = new_canvas(camera->hsize, camera->vsize);
	piece_size = image->height / THREAD_NUM;
	y = 0;
	while (y < THREAD_NUM)
	{
		args[y].image = image;
		args[y].camera = camera;
		args[y].world = world;
		args[y].start = y * piece_size;
		args[y].end = (y + 1) * piece_size;
		pthread_create(&ids[y], NULL, draw_piece, &args[y]);
		y++;
	}
	y = 0;
	while (y < THREAD_NUM)
		pthread_join(ids[y++], NULL);
	return (image);
}

// t_canvas	*render(t_camera *camera, t_world *world)
// {
// 	t_canvas		*image;
// 	int				y;
// 	int				x;
// 	t_ray			*ray;
// 	t_color			*color;
//
// 	image = new_canvas(camera->hsize, camera->vsize);
// 	y = 0;
// 	while (y < image->height)
// 	{
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			ray = ray_to_pixel(x, y, camera);
// 			color = color_at(world, ray);
// 			image->data[y * image->width + x] = color_to_int(color);
// 			destroy_ray(ray);
// 			free(color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (image);
// }

t_color	*pixel_at(t_canvas *image, int x, int y)
{
	unsigned int	pixel;

	pixel = image->data[y * image->width + x];
	return (new_color(
			((pixel & 0xff0000) >> 16) / 255.0,
			((pixel & 0xff00) >> 8) / 255.0,
			((pixel & 0xff)) / 255.0
		));
}
