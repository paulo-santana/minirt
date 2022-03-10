/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:56:12 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 19:04:29 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "tuple.h"

t_tuple	*add_tuples(t_tuple *a, t_tuple *b)
{
	return (new_tuple(
			a->x + b->x,
			a->y + b->y,
			a->z + b->z,
			a->w + b->w));
}

t_tuple	*subtract_tuples(t_tuple *a, t_tuple *b)
{
	return (new_tuple(
			a->x - b->x,
			a->y - b->y,
			a->z - b->z,
			a->w - b->w));
}

t_tuple	*negate_tuple(t_tuple *a)
{
	return (new_tuple(-a->x, -a->y, -a->z, -a->w));
}
