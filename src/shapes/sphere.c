/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:04:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/16 18:09:23 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "matrix/matrix.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "debug.h"

t_sphere	*new_sphere(void)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->position = new_point(0, 0, 0);
	sphere->radius = 1;
	sphere->transform = identity_matrix();
	sphere->inverse_transform = identity_matrix();
	sphere->material = new_material();
	return (sphere);
}

void	destroy_sphere(void *data)
{
	t_sphere	*sphere;

	sphere = data;
	free(sphere->position);
	free(sphere->transform);
	free(sphere->inverse_transform);
	destroy_material(sphere->material);
	free(sphere);
}

void	set_transform(t_sphere *sphere, t_matrix *t)
{
	free(sphere->transform);
	sphere->transform = t;
	free(sphere->inverse_transform);
	sphere->inverse_transform = inverse(t);
}
