/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 02:54:08 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:03:06 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "structures.h"

void	my_mlx_put_pixel(t_image *img, unsigned int color, int x, int y)
{
	unsigned int	*addr;

	addr = \
	(unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
	*addr = color;
}

int	init_mlx_image(t_image *image, int width, int height, t_data *data)
{
	image->ptr = mlx_new_image(data->mlx, width, height);
	image->data = mlx_get_data_addr(image->ptr, &image->bpp,
			&image->size_line, &image->endian);
	return (1);
}

void	copy_to_mlx_img(t_canvas *canvas, t_image *image)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			color = canvas->data[y * canvas->width + x];
			my_mlx_put_pixel(image, color, x, y);
			x++;
		}
		y++;
	}
}
