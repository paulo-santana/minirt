/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:27:02 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 19:57:23 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "structures.h"
#include "tuple/tuple.h"

t_matrix44	*matrix44_multiply(t_matrix44 *a, t_matrix44 *b)
{
	int			row;
	int			col;
	t_matrix44	*result;

	row = 0;
	result = matrix44(NULL);
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result->data[row][col]
				= a->data[row][0] * b->data[0][col]
				+ a->data[row][1] * b->data[1][col]
				+ a->data[row][2] * b->data[2][col]
				+ a->data[row][3] * b->data[3][col];
			col++;
		}
		row++;
	}
	return (result);
}

t_tuple	*matrix44_multiply_tuple(t_matrix44 *a, t_tuple *b)
{
	int		row;
	float	tmp[4];
	t_tuple	*result;

	row = 0;
	while (row < 4)
	{
		tmp[row]
			= a->data[row][0] * b->x
			+ a->data[row][1] * b->y
			+ a->data[row][2] * b->z
			+ a->data[row][3] * b->w;
		row++;
	}
	result = new_tuple(tmp[0], tmp[1], tmp[2], tmp[3]);
	return (result);
}
