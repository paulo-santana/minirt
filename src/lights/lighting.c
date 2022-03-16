/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:24 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 21:03:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include "tuple/tuple.h"
#include "structures.h"

t_color	*get_diffuse(
	t_lighting_args *args, t_color *effective_color, float light_dot_normal)
{
	t_color	*diffuse;
	t_color	*tmp_color;

	if (light_dot_normal < 0)
	{
		diffuse = new_color(0, 0, 0);
	}
	else
	{
		tmp_color = multiply_scalar_color(effective_color,
				args->material->diffuse);
		diffuse = multiply_scalar_color(tmp_color, light_dot_normal);
		free(tmp_color);
	}
	return (diffuse);
}

t_color	*get_ambient(t_lighting_args *args, t_color *effective_color)
{
	t_color	*ambient;

	ambient = multiply_scalar_color(effective_color, args->material->ambient);
	return (ambient);
}

t_color	*calculate_specular(t_lighting_args *args, float reflect_dot_eye)
{
	void	*tmp;
	t_color	*specular;

	if (reflect_dot_eye <= 0)
		specular = new_color(0, 0, 0);
	else
	{
		tmp = multiply_scalar_color(args->light->intensity,
				args->material->specular);
		specular = multiply_scalar_color(tmp,
				pow(reflect_dot_eye, args->material->shininess));
		free(tmp);
	}
	return (specular);
}

t_color	*get_specular(
		t_lighting_args *args, float light_dot_normal, t_tuple *light_v)
{
	t_color	*specular;
	void	*tmp;
	t_tuple	*reflect_v;
	float	reflect_dot_eye;

	if (light_dot_normal < 0)
		specular = new_color(0, 0, 0);
	else
	{
		tmp = negate_tuple(light_v);
		reflect_v = reflect(tmp, args->normal_vector);
		reflect_dot_eye = dot(reflect_v, args->eye_vector);
		free(reflect_v);
		free(tmp);
		specular = calculate_specular(args, reflect_dot_eye);
	}
	return (specular);
}

t_color	*sum_colors(t_color *ambient, t_color *diffuse, t_color *specular)
{
	t_color	*tmp_color;
	t_color	*effective_color;

	tmp_color = add_colors(ambient, diffuse);
	effective_color = add_colors(tmp_color, specular);
	free(tmp_color);
	free(specular);
	free(ambient);
	free(diffuse);
	return (effective_color);
}

t_color	*lighting(t_lighting_args *args)
{
	t_tuple	*tmp_tuple;
	t_tuple	*light_v;
	float	light_dot_normal;
	t_color	*tmp_color;
	t_color	*effective_color;

	effective_color = multiply_colors(
			args->material->color, args->light->intensity);
	tmp_tuple = subtract_tuples(args->light->position, args->position);
	light_v = normalize(tmp_tuple);
	free(tmp_tuple);
	light_dot_normal = dot(light_v, args->normal_vector);
	tmp_color = effective_color;
	effective_color = sum_colors(
			get_ambient(args, effective_color),
			get_diffuse(args, effective_color, light_dot_normal),
			get_specular(args, light_dot_normal, light_v)
			);
	free(light_v);
	free(tmp_color);
	return (effective_color);
}