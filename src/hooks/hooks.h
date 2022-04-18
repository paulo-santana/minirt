/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 23:22:49 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/18 02:03:16 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H
# include "../minirt.h"

int		close_screen(t_data *data);
int		keyboard_hook(int keycode, t_data *data);
int		expose_hook(t_data *data);
void	free_data(t_data *data);
#endif /* !WORLD_H */
