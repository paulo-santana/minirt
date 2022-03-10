/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:56:12 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 18:17:15 by psergio-         ###   ########.fr       */
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
