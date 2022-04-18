/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 22:36:43 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/18 02:04:39 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_data(t_data *data)
{
	free(data->canvas->data);
	destroy_camera(data->camera);
	destroy_world(data->world);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->mlx_img.ptr);
}

int	expose_hook(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
	return (0);
}

int	close_screen(t_data *data)
{
	free_data(data);
	exit(1);
	return (0);
}

int	keyboard_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (close_screen(data));
	return (0);
}
