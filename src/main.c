#include "minirt.h"
#include "structures.h"
#include "tuple/tuple.h"
#include <mlx.h>

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
	void	*mlx;
	void	*window;
	t_image	canvas;
} t_data;

#define WIN_WIDTH 900
#define WIN_HEIGHT 550

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
	if (key == 'a')
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

void put_pixel(t_image *img, t_color *color, int x, int y)
{
	unsigned int	*addr;

	addr = (unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
	*addr = color_to_int(color);
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
		put_pixel(&data->canvas, &color, proj->position->x, WIN_HEIGHT - proj->position->y);
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

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	data.canvas.ptr = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.canvas.data = mlx_get_data_addr(data.canvas.ptr, &data.canvas.bpp, &data.canvas.size_line, &data.canvas.endian);
	test_projectile(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.canvas.ptr, 0, 0);
	mlx_hook(data.window, 2, 1, exit_hook, &data);
	mlx_loop(data.mlx);
}