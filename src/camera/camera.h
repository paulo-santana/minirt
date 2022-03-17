/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:08:55 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/17 12:52:24 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "tuple/tuple.h"
# include "matrix/matrix.h"
# include "structures.h"

typedef struct s_camera {
	int			hsize;
	int			vsize;
	float		fov;
	float		pixel_size;
	float		half_width;
	float		half_height;
	t_matrix	*transform;
}	t_camera;

t_camera	*new_camera(int hsize, int vsize, float field_of_view);

t_matrix	*view_transform(t_tuple *from, t_tuple *to, t_tuple *up);

#endif /* !CAMERA_H */
