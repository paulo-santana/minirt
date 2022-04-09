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

# include <stddef.h>
# include "../libft/libft.h"

typedef struct s_tuple {
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_color {
	double	red;
	double	green;
	double	blue;
}	t_color;

typedef struct s_matrix {
	int		size;
	double	data[4][4];
}	t_matrix;

typedef struct s_material {
	t_color	*color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_sphere {
	t_tuple		*position;
	double		radius;
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
	t_list		*lights;
	t_objects	objects;
}	t_world;

typedef enum e_object_types {
	OBJ_SPHERE,
	OBJ_MAX,
}	t_object_types;

typedef struct s_computations {
	double			t;
	void			*object;
	t_object_types	object_type;
	t_tuple			*point;
	t_tuple			*over_point;
	t_tuple			*eyev;
	t_tuple			*normalv;
	int				inside;
}	t_computations;

typedef struct s_ray {
	t_tuple	*origin;
	t_tuple	*direction;
}	t_ray;

typedef struct s_intersection {
	double			t;
	void			*object;
	t_object_types	object_type;
}	t_intersection;

typedef struct s_intersections {
	size_t			count;
	size_t			size;
	int				is_sorted;
	t_intersection	**intersections;
}	t_intersections;

typedef struct s_canvas {
	unsigned int	*data;
	int				width;
	int				height;
}	t_canvas;

#endif /* !STRUCTURES_H */
