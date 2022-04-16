/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:30:08 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/16 16:30:12 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_scene_object_param(t_scene_object_param *head)
{
	t_scene_object_param	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->identifier)
			free(head->identifier);
		if (head->cordinates)
			free(head->cordinates);
		if (head->color)
			free(head->color);
		if (head->orientation_vector)
			free(head->orientation_vector);
		if (head)
			free(head);
		head = tmp;
	}
}

void	free_scene_light_param(t_scene_light_param *head)
{
	t_scene_light_param	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->l_light_point)
			free(head->l_light_point);
		if (head->l_color)
			free(head->l_color);
		if (head)
			free(head);
		head = tmp;
	}
}

void	add_scene_object_param(t_parameters *p, t_scene_object_param *node)
{
	node->next = p->object_head;
	p->object_head = node;
}

void	add_scene_light_param(t_parameters *p, t_scene_light_param *node)
{
	node->next = p->light_head;
	p->light_head = node;
}
