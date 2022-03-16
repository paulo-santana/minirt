#include "libft.h"
#include "lights/lights.h"
#include "matrix/matrix.h"
#include "minirt.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "debug.h"
#include "world/world.h"
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 800

typedef struct s_projectile {
	t_tuple	*position;
	t_tuple	*velocity;
} t_projectile;

typedef struct s_environment {
	t_tuple	*gravity;
	t_tuple	*wind;
} t_environment;

typedef struct s_image {
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
} t_image;

typedef struct s_canvas {
	unsigned int	*data;
	int				width;
	int				height;
}	t_canvas;

typedef struct s_data {
	void			*mlx;
	void			*window;
	t_sphere		*sphere;
	t_point_light	*light;
	t_image			mlx_img;
	t_canvas		*canvas;
	t_world			*world;
} t_data;

t_projectile	*tick(t_environment *environment, t_projectile *projectile)
{
	t_tuple 		*position;
	t_tuple 		*acc;
	t_tuple 		*velocity;
	t_projectile	*new_proj;

	position = add_tuples(projectile->position, projectile->velocity);
	acc = add_tuples(environment->gravity, environment->wind);
	velocity = add_tuples(projectile->velocity, acc);
	new_proj = malloc(sizeof(t_projectile));
	new_proj->position = position;
	new_proj->velocity = velocity;
	free(acc);
	return (new_proj);
}

unsigned int color_to_int(t_color *color)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = color->red * 255;
	green = color->green * 255;
	blue = color->blue * 255;
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return (red << 16 | green << 8 | blue);
}

void put_pixel(t_canvas *img, t_color *color, int x, int y)
{
	img->data[y * img->width + x] = color_to_int(color);
}

void	my_mlx_put_pixel(t_image *img, unsigned int color, int x, int y)
{
	unsigned int	*addr;

	addr = (unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
	*addr = color;
}

void	draw_canvas_mlx(t_canvas *canvas, t_image *mlx_img)
{
	int		i;
	int 	j;
	int		pixel_x;
	int		pixel_y;

	i = 0;
	int width = mlx_img->size_line / (mlx_img->bpp / 8);
// -	addr = (unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
	while (i < width)
	{
		j = 0;
		int height = WIN_HEIGHT;
		while (j < height)
		{
			int limit = WIN_HEIGHT > WIN_WIDTH ? WIN_WIDTH : WIN_HEIGHT;
			pixel_x = (i * canvas->width) / limit;
			pixel_y = (j * canvas->height) / limit;
			if (pixel_x > canvas->width || pixel_y > canvas->height)
				return ;
			unsigned int color = canvas->data[pixel_y * canvas->width + pixel_x];
			my_mlx_put_pixel(mlx_img, color, i, j);
			j++;
		}
		i++;
	}
}

void	test_projectile(t_data *data)
{
	t_projectile *proj;
	t_projectile *tmp_proj;
	t_environment *env;
	t_tuple *tmp;

	float plane_x = 100;
	float plane_y = 100;

	float pixel_width = plane_x / data->canvas->width;
	float pixel_height = plane_y / data->canvas->height;

	proj = malloc(sizeof(t_projectile));
	proj->position = new_point(0, 1, 0);
	tmp = new_vector(1, 1.8, 0);
	proj->velocity = normalize(tmp);
	free(tmp);
	tmp = multiply_scalar(proj->velocity, 11.25);
	free(proj->velocity);
	proj->velocity = tmp;

	env = malloc(sizeof(t_projectile));
	env->gravity = new_vector(0, -0.1, 0);
	env->wind = new_vector(-0.01, 0, 0);

	t_color color;
	color.blue = 0.1;
	color.green = 0.4;
	color.red = 0.8;
	while (proj->position->y > 0)
	{
		tmp_proj = tick(env, proj);
		int pixel_x = proj->position->x * pixel_width;
		int pixel_y = proj->position->y * pixel_height;
		put_pixel(data->canvas, &color, pixel_x, data->canvas->height - pixel_y);
		free(proj->position);
		free(proj->velocity);
		free(proj);
		proj = tmp_proj;
	}
	draw_canvas_mlx(data->canvas, &data->mlx_img);
	free(proj->position);
	free(proj->velocity);
	free(proj);
	free(env->gravity);
	free(env->wind);
	free(env);
}

int	init_mlx_image(t_image *image, int width, int height, t_data *data)
{
	image->ptr = mlx_new_image(data->mlx, width, height);
	image->data = mlx_get_data_addr(image->ptr, &image->bpp,
			&image->size_line, &image->endian);
	return (1);
}

void	draw_clock(t_data *data)
{
	t_tuple	*point;
	t_color	*color;
	t_matrix *rot;
	t_tuple *tmp;

	rot = rotation_z(M_PI_2 / 3);
	point = new_point(0, 1, 0);

	color = new_color(0.6, 0.3, 0.1);
	for (int i = 0; i < 12; i++)
	{
		int x, y;

		x = (point->x) * 150 + WIN_WIDTH / 2.;
		y = (point->y) * 150 + WIN_HEIGHT / 2.;
		if (x >= WIN_WIDTH)
			x = WIN_WIDTH - 1;
		else if (x < 0)
			x = 0;
		if (y >= WIN_HEIGHT)
			y = WIN_HEIGHT - 1;
		else if (y < 0)
			y = 0;

		int size = 4;
		for (int i = x- size; i < x +  size; i++)
			for (int j = y- size; j < y +  size; j++)
				put_pixel(data->canvas, color, i, j);

		tmp = point;
		point = matrix_multiply_tuple(rot, tmp);
		free(tmp);
	}
}

void	reset_intersections(t_intersections *xs)
{
	while (xs->count--)
		free(xs->intersections[xs->count]);
	xs->count = 0;
	xs->is_sorted = 0;
}

t_canvas	*new_canvas(int width, int height)
{
	t_canvas	*canvas;
	int			size;

	canvas = malloc(sizeof(t_canvas));
	size = sizeof(canvas->data) * width * height;
	canvas->data = malloc(size);
	ft_bzero(canvas->data, size);
	canvas->width = width;
	canvas->height = height;
	return (canvas);
}

void	draw_canvas_ascii(t_canvas *canvas)
{
	int		i;
	int 	j;
	int		pixel_x;
	int		pixel_y;
	unsigned int color;
	unsigned int blue;
	char	*buffer;
	char	*palette = " .-:~+*%YOSHD#NM";


	i = 0;
	// int width = mlx_img->size_line / (mlx_img->bpp / 8);
	int width = 100;
	int height = 50;
	buffer = malloc((width + 1) * height + 1);
// -	addr = (unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
	while (i < height)
	{
		j = 0;
		// int height = WIN_HEIGHT;
		while (j < width)
		{
			// int limit = height > width ? width : height;
			pixel_x = (j * canvas->width) / width;
			pixel_y = (i * canvas->height) / height;
			// if (pixel_x > canvas->width || pixel_y > canvas->height)
			// 	return ;
			color = canvas->data[pixel_y * canvas->width + pixel_x];
			// my_mlx_put_pixel(mlx_img, color, i, j);
			blue = (color & 0xff) >> 0;
			char c = palette[(int)(blue / 256. * strlen(palette))];
			buffer[i * (width + 1) + j] = c;
			j++;
		}
		buffer[i * (width + 1) + j] = '\n';
		i++;
	}
	buffer[i * (width + 1) + j + 1] = '\0';
	ft_putstr_fd(buffer, 1);
}

void	draw_sphere(t_data *data)
{
	float wall_z = 1;
	float wall_size = 7;

	float pixel_size = wall_size / data->canvas->width;
	float half = wall_size / 2;

	t_tuple *direction = NULL;
	t_tuple *target = new_point(0, 0, 0);
	t_ray *ray = new_ray(new_point(0, 0, -5), NULL);
	t_color *color = NULL;

	// sphere->material->color->red = 0.3;


	int i;
	int j;

	i = 0;
	while (i < data->canvas->width)
	{
		float world_y = half - pixel_size * i;
		j = 0;
		while (j < data->canvas->height)
		{
			float world_x = -half + pixel_size * j;
			target->x = world_x;
			target->y = world_y;
			target->z = wall_z;
			direction = subtract_tuples(target, ray->origin);
			t_tuple *norm_direction = normalize(direction);
			free(ray->direction);
			ray->direction = norm_direction;
			free(color);
			color = color_at(data->world, ray);
			put_pixel(data->canvas, color, i, j);
			free(direction);
			j++;
		}
		i++;
	}
	draw_canvas_mlx(data->canvas, &data->mlx_img);
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
	draw_canvas_ascii(data->canvas);
}

void	rotate_light(t_data *data, float deg)
{
	t_matrix	*rot;
	t_tuple		*position;

	rot = rotation_y(deg);
	position = data->light->position;
	data->light->position = matrix_multiply_tuple(rot, position);
	// print_tuple(position);
	free(position);
	draw_sphere(data);
}

int	exit_hook(int key, t_data *data)
{
	if (key == 'q')
		exit(0);
	else if (key == 'a')
		rotate_light(data, -.1);
	else if (key == 'd')
		rotate_light(data, .1);
	return (1);
}

int	main(void)
{
	t_data data;
	float canvas_pixels = 200;

	data.canvas = new_canvas(canvas_pixels, canvas_pixels);
	data.light = new_point_light(new_point(-10, 10, -10), new_color(.3, 1, .1));
	data.sphere = new_sphere();
	data.world = default_world();
	set_transform(data.sphere, translation(0, -1, 4));
	free(data.sphere->material->color);
	data.sphere->material->color = new_color(0.1, 0.0, 1);

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	init_mlx_image(&data.mlx_img, WIN_WIDTH, WIN_HEIGHT, &data);
	// test_projectile(&data);
	// draw_clock(&data);
	draw_sphere(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.mlx_img.ptr, 0, 0);
	mlx_hook(data.window, 2, 1, exit_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
