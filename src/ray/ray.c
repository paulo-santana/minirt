/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:15:01 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/13 15:45:35 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "tuple/tuple.h"

t_tuple	*get_position(t_ray *ray, double t)
{
	t_tuple	*distance;
	t_tuple	*new_pos;

	distance = multiply_scalar(ray->direction, t);
	new_pos = add_tuples(ray->origin, distance);
	free(distance);
	return (new_pos);
}

void	destroy_ray(t_ray *ray)
{
	free(ray->direction);
	free(ray->origin);
	free(ray);
}
