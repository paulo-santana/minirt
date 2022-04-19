/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 02:35:03 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:04:07 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lights/lights.h"
#include "matrix/matrix.h"
#include "minirt.h"
#include "parsing/parsing.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "world/world.h"
#include <bits/types/struct_timeval.h>
#include <math.h>
#include <mlx.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <camera/camera.h>
#include <unistd.h>

#define XK_LEFTARROW                     65361 /* U+2190 LEFTWARDS ARROW */
#define XK_UPARROW                       65362  /* U+2191 UPWARDS ARROW */
#define XK_RIGHTARROW                    65363  /* U+2192 RIGHTWARDS ARROW */
#define XK_DOWNARROW                     65364  /* U+2193 DOWNWARDS ARROW */

void	get_params(t_data *data, t_parameters *p)
{
	data->world = new_world();
	data->world->lights = get_world_light_params(p);
	data->world->objects.spheres = get_world_objects_params(p);
	data->camera = get_camera_params(p);
}

void	render_full(t_data *data)
{
	data->canvas = render(data->camera, data->world);
	copy_to_mlx_img(data->canvas, &data->mlx_img);
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_parameters	*p;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nBad arguments", 2);
		return (1);
	}
	data = (t_data){};
	p = malloc(sizeof(t_parameters));
	init_allocated_parameters(p);
	if (file_check(argv[1], p) == -1)
	{
		free_allocated_parameters(p);
		return (1);
	}
	get_params(&data, p);
	free_allocated_parameters(p);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_X, WIND_Y, "MiniRT");
	init_mlx_image(&data.mlx_img, WIN_X, WIND_Y, &data);
	init_hooks(&data);
	render_full(&data);
	mlx_loop(data.mlx);
	return (0);
}
