/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:09:48 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 10:41:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stddef.h>
# include "../libft/libft.h"

typedef enum e_object_types		t_object_types;
typedef struct s_tuple			t_tuple;
typedef struct s_color			t_color;
typedef struct s_matrix			t_matrix;
typedef struct s_material		t_material;
typedef struct s_sphere			t_sphere;
typedef struct s_shape			t_shape;
typedef struct s_point_light	t_point_light;
typedef struct s_objects		t_objects;
typedef struct s_world			t_world;
typedef struct s_ray			t_ray;
typedef struct s_intersection	t_intersection;
typedef struct s_intersections	t_intersections;
typedef struct s_canvas			t_canvas;
typedef struct s_computations	t_computations;

enum e_object_types {
	OBJ_SPHERE,
	OBJ_MAX,
};

struct s_tuple {
	double	x;
	double	y;
	double	z;
	double	w;
};

struct s_color {
	double	red;
	double	green;
	double	blue;
};

struct s_matrix {
	int		size;
	double	data[4][4];
};

struct s_material {
	t_color	*color;
	t_color	*ambient;
	double	diffuse;
	double	specular;
	double	shininess;
};

struct s_sphere {
	t_tuple		position;
	double		radius;
};

struct s_shape {
	t_matrix		*transform;
	t_matrix		*inverse_transform;
	t_material		*material;
	t_object_types	type;
	union {
		t_sphere	sphere_props;
	};
	void			(*intersect)(
			t_shape *shape, t_ray *ray, t_intersections *xs);
	void			(*destroy_fn)(void *data);
};

struct s_point_light {
	t_color	*intensity;
	t_tuple	*position;
};

struct s_objects {
	int		total;
	int		sphere_count;
	t_list	*spheres;
};

struct s_world {
	t_list		*lights;
	t_objects	objects;
};

struct s_computations {
	double			t;
	t_shape			*object;
	t_object_types	object_type;
	t_tuple			*point;
	t_tuple			*over_point;
	t_tuple			*eyev;
	t_tuple			*normalv;
	int				inside;
};

struct s_ray {
	t_tuple	*origin;
	t_tuple	*direction;
};

struct s_intersection {
	double			t;
	void			*object;
	t_object_types	object_type;
};

struct s_intersections {
	size_t			count;
	size_t			size;
	int				is_sorted;
	t_intersection	**intersections;
};

struct s_canvas {
	unsigned int	*data;
	int				width;
	int				height;
};

#endif /* !STRUCTURES_H */
