/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:45:51 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 20:46:27 by psergio-         ###   ########.fr       */
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
