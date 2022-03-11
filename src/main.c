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

void	test_projectile(void)
{
	t_projectile *proj;
	t_projectile *tmp_proj;
	t_environment *env;
	t_tuple *tmp;

	proj = malloc(sizeof(t_projectile));
	proj->position = new_point(0, 1, 0);
	tmp = new_vector(50, 50, 50);
	// proj->velocity = tmp;
	proj->velocity = normalize(tmp);
	free(tmp);
	env = malloc(sizeof(t_projectile));
	env->gravity = new_vector(0, -0.1, 0);
	env->wind = new_vector(-0.01, 0, 0);

	while (proj->position->y > 0)
	{
		printf("the projectile position is p(%f, %f, %f)\n",
				proj->position->x, proj->position->y, proj->position->z);
		tmp_proj = tick(env, proj);
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
	printf("hello, world\n");
}

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

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int	exit_hook(int key)
{
	if (key == 'a')
		exit(0);
	return (1);
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Ray Tracer");
	data.canvas.ptr = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.canvas.data = mlx_get_data_addr(data.canvas.ptr, &data.canvas.bpp, &data.canvas.size_line, &data.canvas.endian);
	mlx_put_image_to_window(data.mlx, data.window, data.canvas.ptr, 0, 0);
	mlx_hook(data.window, 2, 1, exit_hook, &data);
	mlx_loop(data.mlx);
	test_projectile();
}
