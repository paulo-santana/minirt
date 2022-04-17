/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:09:48 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/17 23:40:52 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stddef.h>
# include "../libft/libft.h"

typedef enum e_object_types			t_object_types;
typedef struct s_tuple				t_tuple;
typedef struct s_color				t_color;
typedef struct s_matrix				t_matrix;
typedef struct s_material			t_material;
typedef struct s_sphere				t_sphere;
typedef struct s_cylinder			t_cylinder;
typedef struct s_plane				t_plane;
typedef struct s_shape				t_shape;
typedef struct s_point_light		t_point_light;
typedef struct s_objects			t_objects;
typedef struct s_world				t_world;
typedef struct s_ray				t_ray;
typedef struct s_intersection		t_intersection;
typedef struct s_intersections		t_intersections;
typedef struct s_canvas				t_canvas;
typedef struct s_computations		t_computations;
typedef struct s_scene_object_param	t_scene_object_param;
typedef struct s_parameters			t_parameters;
typedef struct s_data				t_data;
typedef struct s_image				t_image;
typedef struct s_camera				t_camera;

typedef struct s_scene_light_param
{
	double							*l_light_point;
	double							l_britghness;
	double							*l_color;
	struct s_scene_light_param		*next;
}	t_scene_light_param;

struct s_scene_object_param
{
	char							*identifier;
	double							*cordinates;
	double							*color;
	double							*orientation_vector;
	double							diameter;
	double							height;
	struct s_scene_object_param		*next;
};

struct s_parameters
{
	double					a_lighting;
	double					*a_color;
	double					*c_view_point;
	double					*c_orientation_vector;
	double					c_fov;
	t_scene_light_param		*light_head;
	t_scene_object_param	*object_head;
};

enum e_object_types {
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
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

struct s_cylinder {
	t_tuple		position;
	double		max;
	double		min;
	double		radius;
};

struct s_plane {
	t_tuple		position;
};

struct s_shape {
	t_matrix		*transform;
	t_matrix		*inverse_transform;
	t_material		*material;
	t_object_types	type;
	union {
		t_sphere	sphere_props;
		t_plane		plane_props;
		t_cylinder	cylinder_props;
	};
	t_tuple			*(*normal_at)(t_shape *shape, t_tuple *point);
	void			(*intersect)(
			t_shape *shape, t_ray *ray, t_intersections *xs);
	void			(*destroy_fn)(t_shape *data);
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

struct s_image {
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
};

struct s_camera {
	int			hsize;
	int			vsize;
	double		fov;
	double		pixel_size;
	double		half_width;
	double		half_height;
	t_matrix	*transform;
	t_matrix	*inverse_transform;
};

struct s_data {
	void			*mlx;
	void			*window;
	t_image			mlx_img;
	t_canvas		*canvas;
	t_camera		*camera;
	t_tuple			*cam_position;
	t_tuple			*cam_orientation;
	t_world			*world;
	double			last_tick;
	double			resolution;
	double			delta_mouse_x;
	double			delta_mouse_y;
	int				navigation_mode;
	int				rendered;
};

#endif /* !STRUCTURES_H */
