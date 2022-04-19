/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:22:49 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:13:17 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HANDLER_H
# define MLX_HANDLER_H
# include "../minirt.h"

void	init_hooks(t_data *data);
int		close_screen(t_data *data);
int		keyboard_hook(int keycode, t_data *data);
int		expose_hook(t_data *data);
void	free_data(t_data *data);
void	copy_to_mlx_img(t_canvas *canvas, t_image *image);
int		init_mlx_image(t_image *image, int width, int height, t_data *data);
void	my_mlx_put_pixel(t_image *img, unsigned int color, int x, int y);
#endif /* !WORLD_H */
