/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:04:58 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/14 11:04:34 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stdlib.h>
# include "matrix/matrix.h"
# include "structures.h"

typedef struct s_ray {
	t_tuple	*origin;
	t_tuple	*direction;
}	t_ray;

typedef enum e_object_types {
	OBJ_SPHERE,
	OBJ_MAX,
}	t_object_types;

typedef struct s_intersection {
	float			t;
	void			*object;
	t_object_types	object_type;
}	t_intersection;

typedef struct s_intersections {
	int				count;
	int				size;
	int				is_sorted;
	t_intersection	**intersections;
}	t_intersections;

t_ray			*new_ray(t_tuple *origin, t_tuple *direction);
void			destroy_ray(t_ray *ray);

t_tuple			*get_position(t_ray *ray, float t);
void			intersect(
					t_intersections *current_intersections,
					t_sphere *sphere,
					t_ray *ray);
t_intersection	*new_intersection(float t, void *obj, t_object_types obj_type);
t_intersection	*hit(t_intersections *inters);

void			add_intersection(
					t_intersections *intersections,
					t_intersection *new);

void			sort_intersections(t_intersections *inters);

t_ray			*transform(t_ray *ray, t_matrix *matrix);

t_intersections	*new_intersections_list(void);
void			destroy_intersections_list(t_intersections *inters);

#endif /* !RAY_H */
