/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:51:23 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/16 00:51:50 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "libft.h"
#include "lights/lights.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "shapes/shapes.h"

t_world	*new_world(void)
{
	t_world	*world;

	world = ft_calloc(1, sizeof(t_world));
	return (world);
}

void	destroy_shape(void *data)
{
	t_shape	*shape;

	shape = data;
	shape->destroy_fn(shape);
}

void	destroy_world(t_world *world)
{
	ft_lstclear(&world->lights, (void (*)(void *))destroy_point_light);
	ft_lstclear(&world->objects.spheres, destroy_shape);
	free(world);
}
