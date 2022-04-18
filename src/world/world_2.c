/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 01:23:06 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/18 01:33:39 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "libft.h"
#include "lights/lights.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "shapes/shapes.h"

t_color	*set_light_color(t_scene_light_param *light)
{
	t_color	*tmp_color;
	t_color	*color;

	tmp_color = new_color(\
					light->l_color[0], \
					light->l_color[1], \
					light->l_color[2] \
						);
	color = multiply_scalar_color(tmp_color, light->l_britghness);
	free(tmp_color);
	return (color);
}

t_tuple	*set_light_positon(t_scene_light_param *light)
{
	return (new_point(\
					light->l_light_point[0], \
					light->l_light_point[1], \
					light->l_light_point[2] \
						));
}

t_list	*get_world_light_params(t_parameters *p)
{
	t_scene_light_param		*tmp_light;
	t_list					*head_list;
	t_point_light			*point_light;

	head_list = NULL;
	tmp_light = p->light_head;
	while (tmp_light)
	{
		point_light = new_point_light(
				set_light_positon(tmp_light),
				set_light_color(tmp_light));
		ft_lstadd_back(&head_list, ft_lstnew(point_light));
		tmp_light = tmp_light->next;
	}
	return (head_list);
}

