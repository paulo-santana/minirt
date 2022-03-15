/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:09:48 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 12:58:54 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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

#endif /* !STRUCTURES_H */
