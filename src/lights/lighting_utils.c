/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:49:33 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/16 01:56:20 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include "tuple/tuple.h"

t_color	*get_diffuse(
	t_lighting_args *args, t_color *effective_color, double light_dot_normal)
{
	t_color	*diffuse;
	t_color	*tmp_color;

	if (light_dot_normal < 0)
	{
		diffuse = new_color(0, 0, 0);
	}
	else
	{
		tmp_color = multiply_scalar_color(effective_color,
				args->material->diffuse);
		diffuse = multiply_scalar_color(tmp_color, light_dot_normal);
		free(tmp_color);
	}
	return (diffuse);
}

t_color	*get_brighter(t_color *a, t_color *b)
{
	double	a_brightness;
	double	b_brightness;

	a_brightness = a->red + a->green + a->blue;
	b_brightness = b->red + b->green + b->blue;
	if (a_brightness > b_brightness)
		return (new_color(a->red, a->green, a->blue));
	return (new_color(b->red, b->green, b->blue));
}

t_color	*get_ambient(t_lighting_args *args)
{
	t_color	*ambient;

	ambient = multiply_colors(args->material->color, args->material->ambient);
	return (ambient);
}
