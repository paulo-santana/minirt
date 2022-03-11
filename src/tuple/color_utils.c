/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 09:57:37 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 10:01:49 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	*new_color(float red, float green, float blue)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	color->red = red;
	color->green = green;
	color->blue = blue;
	return (color);
}
