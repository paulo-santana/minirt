/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:27:02 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 20:37:37 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "structures.h"
#include "tuple/tuple.h"
#include "debug.h"
#include <stdio.h>

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
	t_matrix	*tmp;
	t_matrix	*result;

	i = 0;
	while (mats[i])
		i++;
	result = mats[--i];
	while (i--)
	{
		tmp = result;
		result = matrix_multiply(tmp, mats[i]);
		free(tmp);
	}
	return (result);
}

t_tuple	*matrix_multiply_tuple(t_matrix *a, t_tuple *b)
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

t_matrix	*transpose(t_matrix *matrix)
{
	int		i;
	int		j;
	float	tmp;

	i = 0;
	while (i < matrix->size)
	{
		j = i;
		while (j < matrix->size)
		{
			tmp = matrix->data[i][j];
			matrix->data[i][j] = matrix->data[j][i];
			matrix->data[j][i] = tmp;
			j++;
		}
		i++;
	}
	return (matrix);
}

t_matrix	*inverse(t_matrix *matrix)
{
	t_matrix	*inversed;
	int			row;
	int			col;
	float		cofact;
	float		determn;

	if (!is_invertible(matrix))
		return (NULL);
	inversed = new_matrix(matrix->size, NULL);
	determn = determinant(matrix);
	row = 0;
	while (row < matrix->size)
	{
		col = 0;
		while (col < matrix->size)
		{
			cofact = cofactor(matrix, row, col);
			inversed->data[col][row] = cofact / determn;
			col++;
		}
		row++;
	}
	return (inversed);
}
