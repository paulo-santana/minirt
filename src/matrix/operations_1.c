/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:27:02 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/19 03:09:51 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "structures.h"
#include "tuple/tuple.h"

t_matrix	*matrix_multiply(t_matrix *a, t_matrix *b)
{
	int			row;
	int			col;
	t_matrix	*result;

	row = 0;
	result = new_matrix(4, NULL);
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

t_matrix	*matrix_multiply3(t_matrix *a, t_matrix *b, t_matrix *c)
{
	t_matrix	*tmp;
	t_matrix	*result;

	tmp = matrix_multiply(c, b);
	result = matrix_multiply(tmp, a);
	free(tmp);
	return (result);
}

t_matrix	*matrix_multiply_n(t_matrix **mats)
{
	int			i;
	int			passed_first;
	t_matrix	*tmp;
	t_matrix	*result;

	i = 0;
	while (mats[i])
		i++;
	result = mats[--i];
	passed_first = 0;
	while (i--)
	{
		tmp = result;
		result = matrix_multiply(tmp, mats[i]);
		if (passed_first)
			free(tmp);
		passed_first = 1;
	}
	return (result);
}

t_tuple	*matrix_multiply_tuple(t_matrix *a, t_tuple *b)
{
	int		row;
	double	tmp[4];
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

t_matrix	*transpose(t_matrix *matrix)
{
	int			i;
	int			j;
	t_matrix	*transposed;

	transposed = new_matrix(4, NULL);
	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			transposed->data[i][j] = matrix->data[j][i];
			j++;
		}
		i++;
	}
	return (transposed);
}
