/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:37:16 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/19 03:00:57 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray/ray.h"
#include "structures.h"
#include <stddef.h>
#include <stdio.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

t_canvas	*new_canvas(int width, int height)
{
	t_canvas	*canvas;
	size_t		size;

	canvas = malloc(sizeof(t_canvas));
	size = sizeof(canvas->data) * (size_t)width * (size_t)height;
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

	red = (unsigned int)round(color->red * 255);
	green = (unsigned int)round(color->green * 255);
	blue = (unsigned int)round(color->blue * 255);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return (red << 16 | green << 8 | blue);
}

t_canvas	*render(t_camera *camera, t_world *world)
{
	t_canvas		*image;
	int				y;
	int				x;
	t_ray			*ray;
	t_color			*color;

	image = new_canvas(camera->hsize, camera->vsize);
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			ray = ray_to_pixel(x, y, camera);
			color = color_at(world, ray);
			image->data[y * image->width + x] = color_to_int(color);
			destroy_ray(ray);
			free(color);
			x++;
		}
		y++;
	}
	return (image);
}

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
