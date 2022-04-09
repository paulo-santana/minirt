/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:16:34 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 14:32:25 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	is_point(t_tuple *tuple)
{
	return (tuple->w == 1.0);
}

int	is_vector(t_tuple *tuple)
{
	return (tuple->w == 0.0);
}

int	tuple_equals(t_tuple *a, t_tuple *b)
{
	return (
		dequals(a->x, b->x)
		&& dequals(a->y, b->y)
		&& dequals(a->z, b->z)
		&& dequals(a->w, b->w)
	);
}

t_tuple	*normal_at(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple		*object_normal;
	t_tuple		*tmp;
	t_tuple		*world_normal;
	t_tuple		*object_point;
	t_matrix	*transposed;

	object_point = matrix_multiply_tuple(sphere->inverse_transform, world_point);
	tmp = new_point(0, 0, 0);
	object_normal = subtract_tuples(object_point, tmp);
	free(object_point);
	free(tmp);
	transposed = transpose(sphere->inverse_transform);
	tmp = matrix_multiply_tuple(transposed, object_normal);
	free(transposed);
	tmp->w = 0;
	world_normal = normalize(tmp);
	free(tmp);
	free(object_normal);
	return (world_normal);
}
