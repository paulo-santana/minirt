/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:16:34 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 16:06:49 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "structures.h"

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
