/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:00:53 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/14 11:17:49 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix/matrix.h"
#include "ray.h"
#include "structures.h"

t_ray	*transform(t_ray *ray, t_matrix *matrix)
{
	t_ray	*new;
	t_tuple	*origin;
	t_tuple	*direction;

	origin = matrix_multiply_tuple(matrix, ray->origin);
	direction = matrix_multiply_tuple(matrix, ray->direction);
	new = new_ray(origin, direction);
	return (new);
}
