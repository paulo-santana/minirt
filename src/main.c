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

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define XK_leftarrow                     65361 /* U+2190 LEFTWARDS ARROW */
#define XK_uparrow                       65362  /* U+2191 UPWARDS ARROW */
#define XK_rightarrow                    65363  /* U+2192 RIGHTWARDS ARROW */
#define XK_downarrow                     65364  /* U+2193 DOWNWARDS ARROW */

typedef struct s_image {
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
} t_image;

typedef struct s_rotation {
	int	x_plus;
	int x_minus;
	int y_plus;
	int y_minus;
	int z_plus;
	int z_minus;
}	t_rotation;

typedef struct s_movement {
	int	forward;
	int backward;
	int left;
	int right;
	int up;
	int down;
}	t_movement;

typedef struct s_data {
	void			*mlx;
	void			*window;
	t_image			mlx_img;
	t_canvas		*canvas;
	t_camera		*camera;
	t_tuple			*cam_position;
	t_tuple			*cam_orientation;
	t_world			*world;
	t_movement		movement;
	t_rotation		rotation;
	double			last_tick;
	double			resolution;
	double			delta_mouse_x;
	double			delta_mouse_y;
	int				navigation_mode;
	int				rendered;
} t_data;

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
		pixel_y = (int)round(((float)y / (float)height) * (float)canvas->height);
		while (x < width)
		{
			// int limit = WIN_HEIGHT > WIN_WIDTH ? WIN_WIDTH : WIN_HEIGHT;
			pixel_x = (int)roundf(((float)x / (float)width) * (float)canvas->width);
			if (pixel_x > canvas->width || pixel_y > canvas->height)
				return ;
			unsigned int color = canvas->data[pixel_y * canvas->width + pixel_x];
			my_mlx_put_pixel(mlx_img, color, x, y);
			x++;
		}
		y++;
	}
}

int	init_mlx_image(t_image *image, int width, int height, t_data *data)
{
	image->ptr = mlx_new_image(data->mlx, width, height);
	image->data = mlx_get_data_addr(image->ptr, &image->bpp,
			&image->size_line, &image->endian);
	return (1);
}

t_tuple *get_cam_rotation(t_data *data)
{
	return (new_tuple(data->cam_orientation->x,
			data->cam_orientation->y,
			data->cam_orientation->z,
			data->cam_orientation->w));
}

void	draw_canvas_ascii(t_canvas *canvas)
{
	int		i;
	int 	j;
	int		pixel_x;
	int		pixel_y;
	unsigned int color;
	unsigned int avg;
	char	*buffer;
	char	*palette = " .-~+*%YOSHD#NM";

	i = 0;
	// int width = mlx_img->size_line / (mlx_img->bpp / 8);
	int width = 100;
	int height = 50;
	buffer = malloc((size_t)(width + 1) * (size_t)height + 1);
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
			avg = ((color & 0xff0000) >> 16) + ((color & 0xff00) >> 8) + (color & 0xff);
			avg /= 3;
			char c = palette[(int)(avg / 256. * (double)strlen(palette))];
			buffer[i * (width + 1) + j] = c;
			j++;
		}
		buffer[i * (width + 1) + j] = '\n';
		i++;
	}
	buffer[i * (width + 1)] = '\0';
	ft_putstr_fd(buffer, 1);
	free(buffer);
}

void draw_spheres(t_data *data)
{
	free(data->canvas);
	data->canvas = render(data->camera, data->world);
	draw_canvas_mlx(data->canvas, &data->mlx_img);
	draw_canvas_ascii(data->canvas);
	// printf("desenhando na tela...\n");
	// sleep(1);
	mlx_put_image_to_window(data->mlx, data->window, data->mlx_img.ptr, 0, 0);
}

				/*
				* BÁFICA 
				*/
static void	set_cylinder_props_position(t_shape *shape, t_scene_object_param *obj)
{
	shape->cylinder_props.position.x = obj->cordinates[0];
	shape->cylinder_props.position.y = obj->cordinates[1];
	shape->cylinder_props.position.z = obj->cordinates[2];
	shape->cylinder_props.max = obj->height * 0.5;
	shape->cylinder_props.min = - obj->height * 0.5;
	shape->sphere_props.radius = obj->diameter * 0.5;
}

static void	set_plane_props_position(t_shape *shape, t_scene_object_param *obj)
{
	shape->sphere_props.position.x = obj->cordinates[0];
	shape->sphere_props.position.y = obj->cordinates[1];
	shape->sphere_props.position.z = obj->cordinates[2];
}

static void	set_sphere_props_position(t_shape *shape, t_scene_object_param *obj)
{
	shape->sphere_props.position.x = obj->cordinates[0];
	shape->sphere_props.position.y = obj->cordinates[1];
	shape->sphere_props.position.z = obj->cordinates[2];
	shape->sphere_props.radius = obj->diameter * 0.5;
}

static void	set_props(t_shape *shape, t_scene_object_param *obj)
{
	if (!ft_strcmp(obj->identifier, "sp"))
		set_sphere_props_position(shape, obj);
	if (!ft_strcmp(obj->identifier, "pl"))
		set_plane_props_position(shape, obj);
	if (!ft_strcmp(obj->identifier, "cy"))
		set_cylinder_props_position(shape, obj);
}

static void	set_color(t_shape *shape, t_scene_object_param *obj)
{
	shape->material->color = new_color(\
								obj->color[0], \
								obj->color[1], \
								obj->color[2] \
									);
}

static t_shape	*get_scene_shape(t_scene_object_param *obj)
{
	if (!ft_strcmp(obj->identifier, "sp"))
		return (new_sphere());
	else if (!ft_strcmp(obj->identifier, "pl"))
		return (new_plane());
	else if (!ft_strcmp(obj->identifier, "cy"))
		return (new_cylinder());
	else
		return (NULL);
}

static void	set_ambient(t_shape *shape, t_parameters *p)
{
	t_color	*tmp_color;

	tmp_color = new_color(\
						p->a_color[0], \
						p->a_color[1], \
						p->a_color[2] \
							);
	shape->material->ambient = multiply_scalar_color(tmp_color, p->a_lighting);
	free(tmp_color);
}

static t_list	*get_world_objects_params(t_parameters *p)
{
	t_scene_object_param	*tmp_obj;
	t_list					*head_list;
	t_shape					*shape;

	head_list = NULL;
	tmp_obj = p->object_head;
	while (tmp_obj)
	{
		shape = get_scene_shape(tmp_obj);
		set_ambient(shape, p);
		set_props(shape, tmp_obj);
		set_color(shape, tmp_obj);
		if (!head_list)
			head_list = ft_lstnew(shape);
		else
			ft_lstadd_back(&head_list, ft_lstnew(shape));
		tmp_obj = tmp_obj->next;
	}
	return (head_list);
}

static t_color	*set_light_color(t_scene_light_param *light)
{
	t_color	*tmp_color;
	t_color	*color;

	tmp_color = new_color(\
					light->l_color[0], \
					light->l_color[1], \
					light->l_color[2] \
						);
	color = multiply_scalar_color(tmp_color, light->l_britghness);
	free(tmp_color);
	return (color);
}

static t_tuple	*set_light_positon(t_scene_light_param *light)
{
	return (new_point(\
					light->l_light_point[0], \
					light->l_light_point[1], \
					light->l_light_point[2] \
						));
}

static t_list	*get_world_light_params(t_parameters *p)
{
	t_scene_light_param		*tmp_light;
	t_list					*head_list;
	t_point_light			*point_light;

	head_list = NULL;
	tmp_light = p->light_head;
	while (tmp_light)
	{
		point_light = new_point_light(set_light_positon(p->light_head), set_light_color(p->light_head));
		if (!head_list)
			head_list = ft_lstnew(point_light);
		else
			ft_lstadd_back(&head_list, ft_lstnew(point_light));
		tmp_light = tmp_light->next;
	}
	return (head_list);
}

static t_camera	*get_camera_params(t_parameters *p)
{
	t_camera	*camera;

	camera = new_camera(0, 0, 0);
	camera->fov = p->c_fov;
	return (camera);
}

void	get_params(t_data *data, t_parameters *p)
{
	data->world = new_world();
	data->world->lights = get_world_light_params(p);
	data->world->objects.spheres = get_world_objects_params(p);
	data->camera = get_camera_params(p);
}

				/*
				* BÁFICA 
				*/

void	generate_world(t_data *data)
{
	t_world *world = new_world();
	t_shape *floors = new_plane();
	t_matrix *transforms[5];
	set_transform(floors, scaling(10, 0.01, 10));
	floors->material->color->red = .5;
	floors->material->color->green = .9;
	floors->material->color->blue = .6;
	floors->material->specular = 0;

	t_shape *wall = new_plane();
	transforms[0] = rotation_x(M_PI_2);
	transforms[1] = translation(0, 0, 4.5);
	transforms[2] = NULL;
	t_matrix *trans = matrix_multiply_n(transforms);
	set_transform(wall, trans);
	wall->material->specular = .1;

	add_sphere(world, wall);

	wall = new_plane();
	transforms[0] = rotation_x(M_PI_2);
	transforms[1] = translation(0, 0, -13.5);
	transforms[2] = NULL;
	trans = matrix_multiply_n(transforms);
	set_transform(wall, trans);
	wall->material->color->red = .1;
	wall->material->color->green = .8;
	wall->material->color->blue = 1;

	t_shape *middle = new_sphere();
	set_transform(middle, translation(0.5, 1, 0.0));
	middle->material->color->red = 0.3;
	middle->material->color->green = 0.4;
	middle->material->color->blue = 0.8;
	middle->material->diffuse = .9;
	middle->material->ambient = new_color(0.9, 0.1, 0.2);
	middle->material->specular = 1;

	t_shape *cyl1 = new_cylinder();
	transforms[0] = rotation_x(1);
	transforms[1] = rotation_y(-2);
	transforms[2] = translation(5, 2, 3);
	transforms[3] = NULL;
	trans = matrix_multiply_n(transforms);
	set_transform(cyl1, trans);

	t_shape *right = new_sphere();
	set_transform(right,translation(-1.5, 1, 0));
	right->material->color->red = 0.1;
	right->material->color->blue = 0.1;
	right->material->diffuse = 0.7;
	right->material->specular = 0.3;

	t_shape *left = new_sphere();
	set_transform(left, matrix_multiply(translation(3.1, 1, 0), scaling(1, 1, 1)));
	left->material->color->green = 0.4;
	left->material->color->blue = 0.4;
	left->material->diffuse = 0.7;
	left->material->specular = 0.9;

	t_point_light *light = new_point_light(new_point(-10, 10, -10), new_color(.5, .5, .5));
	// t_point_light *light2 = new_point_light(new_point(-1, 1.0, -2), new_color(.5, .5, .5));
	float ratio = (float)WIN_WIDTH / WIN_HEIGHT;
	float size = (float)(WIN_WIDTH * data->resolution);
	t_camera *camera = new_camera((int)size, (int)(size / ratio), M_PI / 3);
	set_camera_transform(camera, view_transform(
				new_point(0, 1.5, -5),
				new_point(0, 1, 0),
				new_vector(0, 1, 0)));
	add_light(world, light);
	// add_light(world, light2);
	// t_point_light *light2 = new_point_light(new_point(10, 10, -10), new_color(.5, .2, 1));
	// add_light(world, light2);
	add_sphere(world, floors);
	add_sphere(world, wall);
	add_sphere(world, right);
	add_sphere(world, middle);
	add_sphere(world, left);
	add_sphere(world, cyl1);
	data->world = world;
	data->camera = camera;
	data->cam_position = new_point(0, 1, -4.5);
}

int	key_release_hook(int key, t_data *data)
{
	if (key == 'q')
	{
		destroy_world(data->world);
		exit(0);
	}
	else if (key == 'w')
		data->movement.forward = 0;
	else if (key == 's')
		data->movement.backward = 0;
	else if (key == 'a')
		data->movement.left = 0;
	else if (key == 'd')
		data->movement.right = 0;
	else if (key == 'k')
		data->movement.up = 0;
	else if (key == 'j')
		data->movement.down = 0;
	else if (key == XK_uparrow)
		data->rotation.x_plus = 0;
	else if (key == XK_downarrow)
		data->rotation.x_minus = 0;
	else if (key == XK_leftarrow)
		data->rotation.y_plus = 0;
	else if (key == XK_rightarrow)
		data->rotation.y_minus = 0;
	if (key == 'm')
		data->navigation_mode = !data->navigation_mode;
	return (1);
}

int	key_press_hook(int key, t_data *data)
{
	if (key == 'q')
	{
		destroy_world(data->world);
		exit(0);
	}
	else if (key == 'w')
		data->movement.forward = 1;
	else if (key == 's')
		data->movement.backward = 1;
	else if (key == 'a')
		data->movement.left = 1;
	else if (key == 'd')
		data->movement.right = 1;
	else if (key == 'k')
		data->movement.up = 1;
	else if (key == 'j')
		data->movement.down = 1;
	else if (key == XK_uparrow)
		data->rotation.x_plus = 1;
	else if (key == XK_downarrow)
		data->rotation.x_minus = 1;
	else if (key == XK_leftarrow)
		data->rotation.y_plus = 1;
	else if (key == XK_rightarrow)
		data->rotation.y_minus = 1;
	return (1);
}

double milis(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	return ((double)current_time.tv_sec * 1000 + (double)current_time.tv_usec / 1000);
}

void print_fps(t_data *data, double delta_time)
{
	double seconds;
	char buff[100];

	seconds = 1 / delta_time;
	snprintf(buff, 100, "fps: %f", seconds);
	mlx_string_put(data->mlx, data->window, 10, 10, 0xff5500, buff);
	seconds = 0;
}

void move_camera(t_data *data, t_tuple *target)
{
	if (data->movement.right)
		target->x = 1;
	else if (data->movement.left)
		target->x = -1;

	if (data->movement.up)
		target->y = 1;
	else if (data->movement.down)
		target->y = -1;

	if (data->movement.forward)
		target->z = 1;
	else if (data->movement.backward)
		target->z = -1;
	else
		target->z = 0;
}

void get_mouse_delta(t_data *data, double *x, double *y)
{
	int px;
	int py;

	mlx_mouse_get_pos(data->mlx, data->window, &px, &py);
	// -1  0  1;
	*x = (double)px / (double)WIN_WIDTH * 2. - 1.;
	*y = (double)py / (double)WIN_HEIGHT * 2. - 1.;
	data->delta_mouse_x = *x;
	data->delta_mouse_y = *y;
	// printf("mouse x: %i, y: %i\n", px, py);
	// printf("mouse x: %.15lf, y: %.15lf\n", data->delta_mouse_x, data->delta_mouse_y);
}

void rotate_camera(t_data *data, double delta_time)
{
	double mousex, mousey;
	double rot_speed = M_PI * .5;

	(void)delta_time;
	get_mouse_delta(data, &mousex, &mousey);
	data->cam_orientation->y += rot_speed * mousex;
	data->cam_orientation->x += rot_speed * mousey;
}

int is_moving(t_data *data)
{
	return (
			data->movement.forward ||
			data->movement.backward ||
			data->movement.left ||
			data->movement.right ||
			data->movement.up ||
			data->movement.down ||
			data->rotation.x_plus ||
			data->rotation.y_plus ||
			data->rotation.z_plus ||
			data->rotation.x_minus ||
			data->rotation.y_minus ||
			data->rotation.z_minus
			);
}

void print_stats(t_data *data)
{
	printf("cam: yaw: %.2f, pitch: %.2f, roll: %.2f\n",
			data->cam_orientation->y,
			data->cam_orientation->x,
			data->cam_orientation->z);
}

double deg_to_rad(double degree)
{
	return degree * M_PI / 180;
}

double rad_to_deg(double radian)
{
	return radian * 180 / M_PI;
}

void center_mouse(t_data *data)
{
	mlx_mouse_move(data->mlx, data->window, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void navigate(t_data *data)
{
	double delta_time;
	double current_time;
	t_tuple *distance;
	static t_tuple up = {0, 1, 0, 0};
	t_tuple forward = {0, 0, 1, 0};
	t_tuple target = {0, 0, 1, 0};
	t_tuple *look_at;
	t_tuple *tmp;
	t_tuple *direction;
	double cam_speed = 2;

	data->rendered = 0;
	current_time = milis();
	delta_time = (current_time - data->last_tick) / 1000;
	data->last_tick = current_time;

	// if (is_moving(data))
	{
		move_camera(data, &target);
		if (data->cam_orientation->x < deg_to_rad(-90))
			data->cam_orientation->x = deg_to_rad(-90);
		else if (data->cam_orientation->x > deg_to_rad(90))
			data->cam_orientation->x = deg_to_rad(90);

		t_matrix *roty = rotation_y(data->cam_orientation->y);
		t_matrix *rotx = rotation_x(data->cam_orientation->x);
		t_matrix *cam_rotation = matrix_multiply(roty, rotx);
		free(roty);
		free(rotx);
		direction = matrix_multiply_tuple(cam_rotation, &target);
		distance = multiply_scalar(direction, cam_speed * delta_time);
		tmp = data->cam_position;
		data->cam_position = add_tuples(data->cam_position, distance);
		free(tmp);

		free(direction);
		direction = matrix_multiply_tuple(cam_rotation, &forward);
		look_at = add_tuples(data->cam_position, direction);
		destroy_camera(data->camera);

		float ratio = (float)WIN_WIDTH / WIN_HEIGHT;
		float size = (float)(WIN_WIDTH * data->resolution);
		tmp = matrix_multiply_tuple(cam_rotation, &up);
		t_matrix *view = view_transform(data->cam_position, look_at, tmp);
		data->camera = new_camera((int)size, (int)(size / ratio), M_PI / 3);
		set_camera_transform(data->camera, view);
		free(tmp);
		free(look_at);
	}
	// free(data->canvas);

	draw_spheres(data);
	rotate_camera(data, delta_time);
	center_mouse(data);
	print_fps(data, delta_time);
	// mlx_clear_window(data->mlx, data->window);
}

void render_full(t_data *data)
{
	t_canvas *canvas;

	if (data->rendered)
		return ;
	data->rendered = 1;
	mlx_string_put(data->mlx, data->window, 0, 0, 0xff, "Teste");
	canvas = new_canvas(WIN_WIDTH, WIN_HEIGHT);
	free(data->canvas);
	data->canvas = canvas;
	set_camera_dimensions(data->camera, data->canvas);
	mlx_mouse_show(data->mlx, data->window);
	draw_spheres(data);
	mlx_string_put(data->mlx, data->window, 0, 0, 0xff, "testado");
}

int update(t_data *data)
{
	if (data->navigation_mode)
		navigate(data);
	else
		render_full(data);
	return (0);
}

double get_delta_time(t_data *data)
{
	double current;
	double delta;

	current = milis();
	delta = (current - data->last_tick) / 1000;
	data->last_tick = current;
	return (delta);
}

int log_mouse(t_data *data)
{
	double delta_time;
	double mousex, mousey;

	delta_time = get_delta_time(data);
	get_mouse_delta(data, &mousex, &mousey);
	// printf("mousex: %lf\n", mousex);
	// printf("mousey: %lf\n", mousey);
	draw_spheres(data);
	print_fps(data, delta_time);
	return (0);
}

int	main(void)
{
	t_data data;

	data = (t_data){};
	data.navigation_mode = 1;
	data.cam_orientation = new_tuple(-2 * M_PI, -2 * M_PI, 2 * M_PI, 0);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	data.resolution = 0.2;
	init_mlx_image(&data.mlx_img, WIN_WIDTH, WIN_HEIGHT, &data);
	generate_world(&data);
	mlx_hook(data.window, 2, 1, key_press_hook, &data);
	mlx_hook(data.window, 3, 2, key_release_hook, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_mouse_hide(data.mlx, data.window);

	data.last_tick = milis();
	center_mouse(&data);
	mlx_loop(data.mlx);
	return (0);
}
//
// int	main(int argc, char **argv)
// {
// 	t_parameters	*p;
//
// 	if (argc != 2)
// 	{
// 		ft_putendl_fd("Error\nBad arguments", 2);
// 		return (1);
// 	}
// 	p = malloc(sizeof(t_parameters));
// 	init_allocated_parameters(p);
// 	if (file_check(argv[1], p) == -1)
// 		ft_putendl_fd("Erou!", 2);
// 	free_allocated_parameters(p);
// 	return (0);
// }
