#include "lights.h"
#include "tuple/tuple.h"
#include "structures.h"

t_color *lighting(t_lighting_args *args)
{
	t_tuple *tmp_tuple;
	t_tuple *light_v;
	t_tuple *reflect_v;
	t_color *effective_color;
	t_color *ambient;

	float	light_dot_normal;
	float	reflect_dot_eye;
	t_color	*diffuse;
	t_color	*specular;
	t_color	*tmp_color;
	float	factor;

	effective_color = multiply_colors(args->material->color, args->light->intensity);
	tmp_tuple = subtract_tuples(args->light->position, args->position);
	light_v = normalize(tmp_tuple);
	free(tmp_tuple);
	ambient = multiply_scalar_color(effective_color, args->material->ambient);
	light_dot_normal = dot(light_v, args->normal_vector);

	if (light_dot_normal < 0)
	{
		diffuse = new_color(0, 0, 0);
		specular = new_color(0, 0, 0);
	}
	else
	{
		tmp_color = multiply_scalar_color(effective_color, args->material->diffuse);
		diffuse = multiply_scalar_color(tmp_color, light_dot_normal);
		free(tmp_color);
		tmp_tuple = negate_tuple(light_v);
		reflect_v = reflect(tmp_tuple, args->normal_vector);
		reflect_dot_eye = dot(reflect_v, args->eye_vector);
		if (reflect_dot_eye <= 0)
			specular = new_color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, args->material->shininess);
			tmp_color = multiply_scalar_color(args->light->intensity, args->material->specular);
			specular = multiply_scalar_color(tmp_color, factor);
			free(tmp_color);
		}
		free(tmp_tuple);
	}
	tmp_color = add_colors(ambient, diffuse);
	free(effective_color);
	effective_color = add_colors(tmp_color, specular);
	free(tmp_color);
	free(specular);
	return (effective_color);
}
