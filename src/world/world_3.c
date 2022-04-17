/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 01:28:09 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/18 01:33:45 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "libft.h"
#include "lights/lights.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "shapes/shapes.h"

void	set_props(t_shape *shape, t_scene_object_param *obj)
{
	if (!ft_strcmp(obj->identifier, "sp"))
		set_sphere_props_position(shape, obj);
	if (!ft_strcmp(obj->identifier, "pl"))
		set_plane_props_position(shape, obj);
	if (!ft_strcmp(obj->identifier, "cy"))
		set_cylinder_props_position(shape, obj);
}

void	set_color(t_shape *shape, t_scene_object_param *obj)
{
	shape->material->color = new_color(\
								obj->color[0], \
								obj->color[1], \
								obj->color[2] \
									);
}

t_shape	*get_scene_shape(t_scene_object_param *obj)
{
	if (!ft_strcmp(obj->identifier, "sp"))
		return (new_sphere());
	else if (!ft_strcmp(obj->identifier, "pl"))
		return (new_plane());
	else if (!ft_strcmp(obj->identifier, "cy"))
		return (new_cylinder());
	else
		return (NULL);
}

void	set_ambient(t_shape *shape, t_parameters *p)
{
	t_color	*tmp_color;

	tmp_color = new_color(\
						p->a_color[0], \
						p->a_color[1], \
						p->a_color[2] \
							);
	shape->material->ambient = multiply_scalar_color(tmp_color, p->a_lighting);
	free(tmp_color);
}

t_list	*get_world_objects_params(t_parameters *p)
{
	t_scene_object_param	*tmp_obj;
	t_list					*head_list;
	t_shape					*shape;

	head_list = NULL;
	tmp_obj = p->object_head;
	while (tmp_obj)
	{
		shape = get_scene_shape(tmp_obj);
		set_ambient(shape, p);
		set_props(shape, tmp_obj);
		set_color(shape, tmp_obj);
		ft_lstadd_back(&head_list, ft_lstnew(shape));
		tmp_obj = tmp_obj->next;
	}
	return (head_list);
}
