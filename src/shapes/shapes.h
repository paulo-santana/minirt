/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:36 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 21:03:23 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <minirt.h>
# include <structures.h>

t_shape		*new_shape(void);

t_shape		*new_sphere(void);
void		destroy_sphere(t_shape *sphere);
t_tuple		*sphere_normal_at(t_shape *shape, t_tuple *point);

t_shape		*new_plane(void);
void		destroy_plane(t_shape *shape);
void		plane_intersect(t_shape *shape, t_ray *ray, t_intersections *xs);
t_tuple		*plane_normal_at(t_shape *shape, t_tuple *tuple);

void		set_transform(t_shape *sphere, t_matrix *t);
void		set_material(t_shape *shape, t_material *material);

t_material	*new_material(void);
void		destroy_material(void *mat);

t_pattern	*stripe_pattern(t_color *a, t_color *b);
t_color		*stripe_at(t_tuple *point, t_pattern *pattern);

#endif /* !SHAPES_H */
