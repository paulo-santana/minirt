/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:47 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/16 18:11:33 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include <structures.h>

t_world	*new_world(void);
t_world	*default_world(void);
void	add_sphere(t_world *world, t_sphere *sphere);
void	add_light(t_world *world, t_point_light *light);
void	destroy_world(t_world *world);

#endif /* !WORLD_H */
