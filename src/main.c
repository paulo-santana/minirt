#include "libft.h"
#include "lights/lights.h"
#include "matrix/matrix.h"
#include "minirt.h"
#include "parsing/parsing.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "debug.h"
#include "world/world.h"
#include <bits/types/struct_timeval.h>
#include <math.h>
#include <mlx.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <camera/camera.h>
#include <unistd.h>

#define WIN_WIDTH 100
#define WIN_HEIGHT 100

#define XK_leftarrow                     65361 /* U+2190 LEFTWARDS ARROW */
#define XK_uparrow                       65362  /* U+2191 UPWARDS ARROW */
#define XK_rightarrow                    65363  /* U+2192 RIGHTWARDS ARROW */
#define XK_downarrow                     65364  /* U+2193 DOWNWARDS ARROW */

void	my_mlx_put_pixel(t_image *img, unsigned int color, int x, int y)
{
	unsigned int	*addr;

	addr = (unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
	*addr = color;
}

int	init_mlx_image(t_image *image, int width, int height, t_data *data)
{
	image->ptr = mlx_new_image(data->mlx, width, height);
	image->data = mlx_get_data_addr(image->ptr, &image->bpp,
			&image->size_line, &image->endian);
	return (1);
}

static t_camera	*get_camera_params(t_parameters *p)
{
	t_camera	*camera;
	t_tuple		*up;
	t_tuple		*orientation;
	t_tuple		*from;

	camera = new_camera(WIN_WIDTH, WIN_HEIGHT, p->c_fov);
	orientation = new_vector(
			p->c_orientation_vector[0],
			p->c_orientation_vector[1],
			p->c_orientation_vector[2]);
	from = new_point(p->c_view_point[0],
				p->c_view_point[1],
				p->c_view_point[2]);
	up = new_vector(0, 1, 0);
	t_matrix *transform = view_transform(
			from,
			orientation,
			up);
	set_camera_transform(camera, transform);
	free(from);
	free(up);
	return (camera);
}

void	copy_to_mlx_img(t_canvas *canvas, t_image *image)
{
	int			x;
	int			y;
	unsigned	color;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			color = canvas->data[y * canvas->width + x];
			my_mlx_put_pixel(image, color, x, y);
			x++;
		}
		y++;
	}
}

void draw_spheres(t_data *data)
{
	free(data->canvas);
	data->canvas = render(data->camera, data->world);
	copy_to_mlx_img(data->canvas, &data->mlx_img);
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
}

void	get_params(t_data *data, t_parameters *p)
{
	data->world = new_world();
	data->world->lights = get_world_light_params(p);
	data->world->objects.spheres = get_world_objects_params(p);
	data->camera = get_camera_params(p);
	data->cam_position = new_point(p->c_view_point[0],
		p->c_view_point[1],
		p->c_view_point[2]);
}

void render_full(t_data *data)
{
	t_canvas *canvas;
	
	if (data->rendered)
		return ;
	data->rendered = 1;
	canvas = new_canvas(WIN_WIDTH, WIN_HEIGHT);
	free(data->canvas);
	data->canvas = canvas;
	set_camera_dimensions(data->camera, data->canvas);
	mlx_mouse_show(data->mlx, data->window);
	mlx_string_put(data->mlx, data->window, 20, 20, 0xff00, "Teste");
	draw_spheres(data);
	mlx_string_put(data->mlx, data->window, 20, 20, 0xff0000, "Testado");
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_parameters	*p;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nBad arguments", 2);
		return (1);
	}
	data = (t_data){};
	p = malloc(sizeof(t_parameters));
	init_allocated_parameters(p);
	if (file_check(argv[1], p) == -1)
	{
		free_allocated_parameters(p);
		return (1);
	}
	get_params(&data, p);
	free_allocated_parameters(p);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	init_mlx_image(&data.mlx_img, WIN_WIDTH, WIN_HEIGHT, &data);
	mlx_hook(data.window, 2, 1L << 0, keyboard_hook, &data);
	mlx_hook(data.window, 12, 1L << 15, expose_hook, &data);
	mlx_hook(data.window, 17, 1L << 2, close_screen, &data);

	render_full(&data);
	mlx_loop(data.mlx);

	return (0);
}
