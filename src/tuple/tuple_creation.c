/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:37:42 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 14:38:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	*new_tuple(float x, float y, float z, float w)
{
	t_tuple	*tuple;

	tuple = malloc(sizeof(t_tuple));
	if (tuple == NULL)
		exit (90);
	tuple->x = x;
	tuple->y = y;
	tuple->z = z;
	tuple->w = w;
	return (tuple);
}

t_tuple	*new_point(float x, float y, float z)
{
	return (new_tuple(x, y, z, 1.0));
}

t_tuple	*new_vector(float x, float y, float z)
{
	return (new_tuple(x, y, z, 0.0));
}
