/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:57:36 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 13:02:05 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_point_light	*new_point_light(t_tuple *pos, t_color *intensity)
{
	t_point_light	*light;

	light = malloc(sizeof(t_point_light));
	light->intensity = intensity;
	light->position = pos;
	return (light);
}

void	destroy_point_light(t_point_light *light)
{
	free(light->intensity);
	free(light->position);
	free(light);
}
