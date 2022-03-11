/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:45:51 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 22:16:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

float	magnitude(t_tuple *a)
{
	return (sqrt(
			a->x * a->x
			+ a->y * a->y
			+ a->z * a->z
			+ a->w * a->w
		));
}

t_tuple	*normalize(t_tuple *vector)
{
	float	mag;

	mag = magnitude(vector);
	return (new_tuple(
			vector->x / mag,
			vector->y / mag,
			vector->z / mag,
			vector->w / mag
		));
}

t_tuple	*cross(t_tuple *a, t_tuple *b)
{
	return (new_vector(
			a->y * b->z - a->z * b->y,
			a->z * b->x - a->x * b->z,
			a->x * b->y - a->y * b->x
		));
}
