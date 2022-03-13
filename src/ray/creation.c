/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:04:30 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/13 13:05:58 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	*new_ray(t_tuple *origin, t_tuple *direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->origin = origin;
	ray->direction = direction;
	return (ray);
}
