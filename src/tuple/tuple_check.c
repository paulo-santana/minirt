/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:16:34 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 17:28:47 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
		fequals(a->x, b->x)
		&& fequals(a->y, b->y)
		&& fequals(a->z, b->z)
		&& fequals(a->w, b->w)
	);
}
