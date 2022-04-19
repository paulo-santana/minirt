/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 22:36:43 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 02:46:53 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_data(t_data *data)
{
	free(data->canvas->data);
	free(data->canvas);
	destroy_camera(data->camera);
	free(data->cam_position);
	destroy_world(data->world);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->mlx_img.ptr);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

int	expose_hook(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
	return (0);
}

int	close_screen(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

int	keyboard_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (close_screen(data));
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data.window, 2, 1L << 0, keyboard_hook, data);
	mlx_hook(data.window, 12, 1L << 15, expose_hook, data);
	mlx_hook(data.window, 17, 1L << 2, close_screen, data);
}
