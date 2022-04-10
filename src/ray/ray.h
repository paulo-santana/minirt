/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:04:58 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 11:03:58 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stdlib.h>
# include <matrix/matrix.h>
# include <tuple/tuple.h>
# include <structures.h>
# include "lights/lights.h"

t_ray			*new_ray(t_tuple *origin, t_tuple *direction);
void			destroy_ray(t_ray *ray);

t_tuple			*get_position(t_ray *ray, double t);
void			intersect(t_shape *shape, t_ray *ray, t_intersections *xs);
void			sphere_intersect(
					t_shape *sphere,
					t_ray *ray,
					t_intersections *current_intersections);
t_intersection	*new_intersection(double t, void *obj, t_object_types obj_type);
t_intersection	*hit(t_intersections *inters);

void			add_intersection(
					t_intersections *intersections,
					t_intersection *new);

t_intersections	*intersect_world(t_world *world, t_ray *ray);
void			sort_intersections(t_intersections *inters);

t_ray			*transform(t_ray *ray, t_matrix *matrix);

t_intersections	*new_intersections_list(void);
void			destroy_intersections_list(t_intersections *inters);

int				is_shadowed(t_world *world,
					t_tuple *point, t_point_light *light);
t_computations	*prepare_computations(t_intersection *intersection, t_ray *ray);
void			destroy_computations(t_computations *comps);
t_intersections	*intersect_world(t_world *world, t_ray *ray);
t_color			*shade_hit(t_world *world, t_computations *comps);
t_color			*color_at(t_world *world, t_ray *ray);

#endif /* !RAY_H */
