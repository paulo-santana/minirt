/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:04:58 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/13 13:30:06 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stdlib.h>
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
	int		count;
	float	*distances;
}	t_intersections;

t_ray			*new_ray(t_tuple *origin, t_tuple *direction);

t_tuple			*position(t_ray *ray, float t);
t_intersections	*intersect(t_sphere *sphere, t_ray *ray);
t_intersection	*new_intersection(float t, void *obj, t_object_types obj_type);

#endif /* !RAY_H */
