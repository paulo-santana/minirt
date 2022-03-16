/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:09:48 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/16 17:24:59 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../libft/libft.h"

typedef struct s_tuple {
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_color {
	float	red;
	float	green;
	float	blue;
}	t_color;

typedef struct s_matrix {
	int		size;
	float	data[4][4];
}	t_matrix;

typedef struct s_material {
	t_color	*color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

typedef struct s_sphere {
	t_tuple		*position;
	float		radius;
	t_matrix	*transform;
	t_matrix	*inverse_transform;
	t_material	*material;
}	t_sphere;

typedef struct s_point_light {
	t_color	*intensity;
	t_tuple	*position;
}	t_point_light;

typedef struct s_objects {
	int		total;
	int		sphere_count;
	t_list	*spheres;
}	t_objects;

typedef struct s_world {
	t_point_light	*light;
	t_objects		objects;
}	t_world;

typedef enum e_object_types {
	OBJ_SPHERE,
	OBJ_MAX,
}	t_object_types;

typedef struct s_computations {
	float			t;
	void			*object;
	t_object_types	object_type;
	t_tuple			*point;
	t_tuple			*eyev;
	t_tuple			*normalv;
	int				inside;
}	t_computations;

typedef struct s_ray {
	t_tuple	*origin;
	t_tuple	*direction;
}	t_ray;

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

#endif /* !STRUCTURES_H */
