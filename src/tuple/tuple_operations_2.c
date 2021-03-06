/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 03:16:03 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:17:19 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "tuple.h"

double	dot(t_tuple *a, t_tuple *b)
{
	return (
		a->x * b->x
		+ a->y * b->y
		+ a->z * b->z
		+ a->w * b->w
	);
}
