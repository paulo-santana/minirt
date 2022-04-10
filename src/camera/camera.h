/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:08:55 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/17 16:50:58 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "tuple/tuple.h"
# include "matrix/matrix.h"
# include "ray/ray.h"
# include "structures.h"

typedef struct s_camera {
	int			hsize;
	int			vsize;
	double		fov;
	double		pixel_size;
	double		half_width;
	double		half_height;
	t_matrix	*transform;
	t_matrix	*inverse_transform;
}	t_camera;

t_camera		*new_camera(int hsize, int vsize, double field_of_view);
void			set_camera_transform(t_camera *camera, t_matrix *t);
t_ray			*ray_to_pixel(int x, int y, t_camera *camera);
void			destroy_camera(t_camera *camera);
void			set_camera_dimensions(t_camera *camera, t_canvas *canvas);

t_matrix		*view_transform(t_tuple *from, t_tuple *to, t_tuple *up);

t_canvas		*render(t_camera *camera, t_world *world);
// t_canvas		*render(t_camera *camera, t_world *world);
t_color			*pixel_at(t_canvas *image, int x, int y);
t_canvas		*new_canvas(int width, int height);
unsigned int	color_to_int(t_color *color);

#endif /* !CAMERA_H */
