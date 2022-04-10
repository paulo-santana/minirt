/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:06:42 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 16:21:20 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix/matrix.h"
#include "shapes.h"
#include "structures.h"
#include "tuple/tuple.h"

t_tuple	*normal_at(t_shape *shape, t_tuple *world_point)
{
	t_tuple		*world_normal;
	t_tuple		*object_normal;
	t_tuple		*object_point;
	t_tuple		*tmp;
	t_matrix	*transposed_inverse;

	object_point = matrix_multiply_tuple(shape->inverse_transform, world_point);
	object_normal = shape->normal_at(shape, object_point);
	transposed_inverse = transpose(shape->inverse_transform);
	world_normal = matrix_multiply_tuple(transposed_inverse, object_normal);
	world_normal->w = 0;
	free(transposed_inverse);
	free(object_normal);
	free(object_point);
	tmp = world_normal;
	world_normal = normalize(world_normal);
	free(tmp);
	return (world_normal);
}
