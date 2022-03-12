/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:55:54 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 18:57:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <minirt.h>

int	matrix_equals(t_matrix *a, t_matrix *b)
{
	int	i;
	int	j;

	if (a->size != b->size)
		return (0);
	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (j < a->size)
		{
			if (!fequals(a->data[i][j], b->data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_invertible(t_matrix *a)
{
	return (determinant(a) != 0);
}
