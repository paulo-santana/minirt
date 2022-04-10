/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 09:41:28 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 10:15:31 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "structures.h"
#include <stdlib.h>

t_shape	*new_shape(void)
{
	t_shape	*shape;

	shape = malloc(sizeof(t_shape));
	*shape = (t_shape){};
	shape->transform = identity_matrix();
	shape->inverse_transform = identity_matrix();
	shape->material = new_material();
	return (shape);
}

void	set_transform(t_shape *sphere, t_matrix *t)
{
	free(sphere->transform);
	sphere->transform = t;
	free(sphere->inverse_transform);
	sphere->inverse_transform = inverse(t);
}

void	set_material(t_shape *shape, t_material *material)
{
	destroy_material(shape->material);
	shape->material = material;
}
