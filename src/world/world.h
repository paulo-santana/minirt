/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:47 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/18 01:37:56 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include <structures.h>

t_world		*new_world(void);
t_world		*default_world(void);
void		add_sphere(t_world *world, t_shape *sphere);
void		add_light(t_world *world, t_point_light *light);
void		destroy_world(t_world *world);
t_list		*get_world_light_params(t_parameters *p);
t_tuple		*set_light_positon(t_scene_light_param *light);
t_color		*set_light_color(t_scene_light_param *light);
t_list		*get_world_objects_params(t_parameters *p);
void		set_ambient(t_shape *shape, t_parameters *p);
t_shape		*get_scene_shape(t_scene_object_param *obj);
void		set_color(t_shape *shape, t_scene_object_param *obj);
void		set_props(t_shape *shape, t_scene_object_param *obj);
void		set_sphere_props_position(t_shape *shape, t_scene_object_param *obj);
void		set_plane_props_position(t_shape *shape, t_scene_object_param *obj);
void		set_cylinder_props_position(t_shape *shape, t_scene_object_param *obj);
t_matrix	*get_orientation_matrix(double vector[3]);




#endif /* !WORLD_H */
