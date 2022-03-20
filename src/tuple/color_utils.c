/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 09:57:37 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 10:11:49 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <minirt.h>

t_color	*new_color(double red, double green, double blue)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	color->red = red;
	color->green = green;
	color->blue = blue;
	return (color);
}

t_color	*add_colors(t_color *a, t_color *b)
{
	return (new_color(
			a->red + b->red,
			a->green + b->green,
			a->blue + b->blue));
}

t_color	*subtract_colors(t_color *a, t_color *b)
{
	return (new_color(
			a->red - b->red,
			a->green - b->green,
			a->blue - b->blue));
}

t_color	*multiply_scalar_color(t_color *tuple, double value)
{
	return (new_color(
			tuple->red * value,
			tuple->green * value,
			tuple->blue * value));
}

// This is also called Hadamard Product
t_color	*multiply_colors(t_color *a, t_color *b)
{
	return (new_color(
			a->red * b->red,
			a->green * b->green,
			a->blue * b->blue));
}
