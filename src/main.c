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
#include <bits/types/struct_timeval.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <camera/camera.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

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

typedef struct s_data {
	void			*mlx;
	void			*window;
	t_image			mlx_img;
	t_canvas		*canvas;
	t_camera		*camera;
	t_world			*world;
	double			last_tick;
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
	int		y;
	int 	x;
	int		pixel_x;
	int		pixel_y;

	y = 0;
	int height = WIN_HEIGHT;
	int width = mlx_img->size_line / (mlx_img->bpp / 8);
	while (y < height)
	{
		x = 0;
		pixel_y = roundf(((float)y / height) * canvas->height);
		while (x < width)
		{
			// int limit = WIN_HEIGHT > WIN_WIDTH ? WIN_WIDTH : WIN_HEIGHT;
			pixel_x = roundf(((float)x / width) * canvas->width);
			if (pixel_x > canvas->width || pixel_y > canvas->height)
				return ;
			unsigned int color = canvas->data[pixel_y * canvas->width + pixel_x];
			my_mlx_put_pixel(mlx_img, color, x, y);
			x++;
		}
		y++;
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


void	draw_canvas_ascii(t_canvas *canvas)
{
	int		i;
	int 	j;
	int		pixel_x;
	int		pixel_y;
	unsigned int color;
	unsigned int blue;
	char	*buffer;
	char	*palette = " .:-~+*%YOSHD#NM";


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
	free(buffer);
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
	destroy_ray(ray);
	free(color);
}

void draw_spheres(t_data *data)
{
	free(data->canvas);
	data->canvas = render(data->camera, data->world);
	draw_canvas_mlx(data->canvas, &data->mlx_img);
	// draw_canvas_ascii(data->canvas);
	// printf("desenhando na tela...\n");
	// sleep(1);
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
}

void	generate_world(t_data *data)
{
	t_sphere *floors = new_sphere();
	t_matrix *transforms[5];
	set_transform(floors, scaling(10, 0.01, 10));
	floors->material->color->green = .9;
	floors->material->color->blue = .9;
	floors->material->specular = 0;

	t_sphere *left_wall = new_sphere();
	transforms[0] = scaling(10, .01, 10);
	transforms[1] = rotation_x(M_PI_2);
	transforms[2] = rotation_y(-M_PI_4);
	transforms[3] = translation(0, 0, 5);
	transforms[4] = NULL;
	set_transform(left_wall, matrix_multiply_n(transforms));
	left_wall->material->specular = floors->material->specular;
	left_wall->material->color->blue = floors->material->color->blue;
	left_wall->material->color->green = floors->material->color->green;

	t_sphere *right_wall = new_sphere();
	transforms[0] = scaling(10, .01, 10);
	transforms[1] = rotation_x(M_PI_2);
	transforms[2] = rotation_y(M_PI_4);
	transforms[3] = translation(0, 0, 5);
	transforms[4] = NULL;
	set_transform(right_wall, matrix_multiply_n(transforms));
	right_wall->material->specular = floors->material->specular;
	right_wall->material->color->blue = floors->material->color->blue;
	right_wall->material->color->green = floors->material->color->green;

	t_sphere *middle = new_sphere();
	set_transform(middle, translation(-0.5, 1, 0.5));
	middle->material->color->red = 0.1;
	middle->material->color->blue = 0.5;
	middle->material->diffuse = 0.7;
	middle->material->specular = 0.3;

	t_sphere *right = new_sphere();
	set_transform(right, matrix_multiply(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5)));
	right->material->color->red = 0.5;
	right->material->color->blue = 0.1;
	right->material->diffuse = 0.7;
	right->material->specular = 0.3;

	t_sphere *left = new_sphere();
	set_transform(left, matrix_multiply(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)));
	left->material->color->green = 0.8;
	left->material->color->blue = 0.1;
	left->material->diffuse = 0.7;
	left->material->specular = 0.3;

	t_point_light *light = new_point_light(new_point(-10, 10, -10), new_color(1, 1, 1));
	float ratio = (float)WIN_WIDTH / WIN_HEIGHT;
	float size = WIN_WIDTH * .999;
	t_camera *camera = new_camera(size, size / ratio, M_PI / 3);
	set_camera_transform(camera, view_transform(
				new_point(0, 1.5, -5),
				new_point(0, 1, 0),
				new_vector(0, 1, 0)));
	t_world *world = new_world();
	add_light(world, light);
	// t_point_light *light2 = new_point_light(new_point(10, 10, -10), new_color(.5, .2, 1));
	// add_light(world, light2);
	add_sphere(world, floors);
	add_sphere(world, left_wall);
	add_sphere(world, right_wall);
	add_sphere(world, right);
	add_sphere(world, middle);
	add_sphere(world, left);
	data->world = world;
	data->camera = camera;
}

void	rotate_sphere(t_data *data, float deg)
{
	t_matrix	*trans;
	t_sphere	*sphere;
	float x, y;

	x = 2 * cosf(deg);
	y = 2 * sinf(deg);

	sphere = data->world->objects.spheres->next->next->next->next->content;
	trans = translation(x, y, sphere->position->z);
	set_transform(sphere, trans);
	draw_spheres(data);
}

int	exit_hook(int key, t_data *data)
{
	if (key == 'q')
		exit(0);
	else if (key == 'a')
		rotate_sphere(data, .2);
	else if (key == 'd')
		rotate_sphere(data, -.2);
	return (1);
}

double milis(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	return (current_time.tv_sec * 1000. + current_time.tv_usec / 1000.);
}

void print_fps(t_data *data, double delta_time)
{
	double seconds;
	char buff[100];

	seconds = 1 / (delta_time / 1000);
	snprintf(buff, 100, "fps: %f", seconds);
	mlx_string_put(data->mlx, data->window, 10, 10, 0xff5500, buff);
	seconds = 0;
}

int update(t_data *data)
{
	static double rotation;
	static double seconds;
	double current_time;
	double delta_time;
	float rps = .2;

	current_time = milis();
	delta_time = current_time - data->last_tick;
	seconds += delta_time / 1000;
	if (seconds > 1)
	{
		printf("a second has passed\n");
		seconds = 0;
	}
	data->last_tick = current_time;

	rotation += rps * (M_PI * 2) * (delta_time / 1000);
	rotate_sphere(data, rotation);
	print_fps(data, delta_time);
	return (1);
}

int	main(void)
{
	t_data data;

	data.canvas = NULL;
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	init_mlx_image(&data.mlx_img, WIN_WIDTH, WIN_HEIGHT, &data);
	// test_projectile(&data);
	// draw_clock(&data);
	// draw_sphere(&data);
	generate_world(&data);
	// draw_spheres(&data);
	// mlx_put_image_to_window(data.mlx, data.window, data.mlx_img.ptr, 0, 0);
	mlx_hook(data.window, 2, 1, exit_hook, &data);
	mlx_loop_hook(data.mlx, update, &data);
	data.last_tick = milis();
	mlx_loop(data.mlx);
	return (0);
}
