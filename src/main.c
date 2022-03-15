#include "libft.h"
#include "matrix/matrix.h"
#include "minirt.h"
#include "ray/ray.h"
#include "shapes/shapes.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "debug.h"
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>

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
	void		*mlx;
	void		*window;
	t_image		mlx_img;
	t_canvas	*canvas;
} t_data;

#define WIN_WIDTH 120
#define WIN_HEIGHT 80

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

int	exit_hook(int key)
{
	if (key == 'a' || key == 'q')
		exit(0);
	return (1);
}

unsigned int color_to_int(t_color *color)
{
	return (
			((unsigned int)(color->red * 255) << 16)
			+ ((unsigned int)(color->green * 255) << 8)
			+ (color->blue * 255)
		);
}

void put_pixel(t_canvas *img, t_color *color, int x, int y)
{
	img->data[y * img->width + x] = color_to_int(color);
}

void	test_projectile(t_data *data)
{
	t_projectile *proj;
	t_projectile *tmp_proj;
	t_environment *env;
	t_tuple *tmp;

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
		put_pixel(data->canvas, &color, proj->position->x, WIN_HEIGHT - proj->position->y);
		free(proj->position);
		free(proj->velocity);
		free(proj);
		proj = tmp_proj;
	}
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

void	draw_canvas_ascii(t_canvas *canvas)
{
	int		i;
	int 	j;
	int		pixel_x;
	int		pixel_y;
	unsigned int color;
	unsigned int red;
	char	*palette = " .-~:+*%YOHSDNM";

	i = 0;
	// int width = mlx_img->size_line / (mlx_img->bpp / 8);
	int width = 100;
	int height = 50;
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
			red = (color & 0xff00) >> 8;
			char c = palette[(int)(red / 255. * strlen(palette))];
			ft_putchar_fd(c, 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	draw_sphere(t_data *data)
{
	float wall_z = 10;
	float wall_size = 7;
	float canvas_pixels = 500;

	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;

	data->canvas = new_canvas(canvas_pixels, canvas_pixels);
	t_matrix *trans = translation(0, 0, 0);
	t_sphere *sphere = new_sphere(new_point(0, 0, 0), 1);
	set_transform(sphere, trans);
	t_tuple *direction = new_vector(0, 0, 1);
	t_tuple *target = new_point(0, 0, 0);
	t_ray *ray = new_ray(new_point(0, 0, -5), NULL);
	t_intersections *xs = new_intersections_list();
	t_color *color = new_color(0, 0, 0);
	t_intersection *surface;
	// "#######$$$$$%%%%%%*******--------........        "

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
			free(ray->direction);
			t_tuple *norm_direction = normalize(direction);
			ray->direction = norm_direction;
			free(direction);
			intersect(xs, sphere, ray);
			surface = hit(xs);
			if (surface != NULL)
			{
				float dz = sphere->position->z - ray->origin->z;
				color->red = dz - surface->t;
				color->green = powf((dz - surface->t) * .99, 2);
				put_pixel(data->canvas, color, i, j);
				// color->blue = 0.4;
			}
			reset_intersections(xs);
			j++;
		}
		i++;
	}
	// draw_canvas_mlx(data->canvas, &data->mlx_img);
	draw_canvas_ascii(data->canvas);
}

int	main(void)
{
	t_data data;

	// data.mlx = mlx_init();
	// data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	// init_mlx_image(&data.mlx_img, WIN_WIDTH, WIN_HEIGHT, &data);
	// test_projectile(&data);
	// draw_clock(&data);
	draw_sphere(&data);
	// mlx_put_image_to_window(data.mlx, data.window, data.mlx_img.ptr, 0, 0);
	// mlx_hook(data.window, 2, 1, exit_hook, &data);
	// mlx_loop(data.mlx);
	return (0);
}
