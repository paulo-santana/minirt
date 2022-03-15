/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:04:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 13:15:17 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix/matrix.h"
#include "shapes.h"
#include "structures.h"

t_sphere	*new_sphere(t_tuple *position, float radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->position = position;
	sphere->radius = radius;
	sphere->transform = identity_matrix();
	sphere->inverse_transform = inverse(sphere->transform);
	sphere->material = new_material();
	return (sphere);
}

void	destroy_sphere(t_sphere *sphere)
{
	free(sphere->position);
	free(sphere->transform);
	free(sphere->inverse_transform);
	free(sphere);
}

void	set_transform(t_sphere *sphere, t_matrix *t)
{
	free(sphere->transform);
	sphere->transform = t;
	free(sphere->inverse_transform);
	sphere->inverse_transform = inverse(t);
}
