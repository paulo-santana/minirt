/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:04:46 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/14 12:06:11 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "structures.h"

t_sphere	*new_sphere(t_tuple *position, float radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->position = position;
	sphere->radius = radius;
	return (sphere);
}

void	destroy_sphere(t_sphere *sphere)
{
	free(sphere->position);
	free(sphere->transform);
	free(sphere);
}
