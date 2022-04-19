/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 03:08:55 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:09:58 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "structures.h"
#include "tuple/tuple.h"

t_matrix	*inverse(t_matrix *matrix)
{
	t_matrix	*inversed;
	int			row;
	int			col;
	double		cofact;
	double		determn;

	determn = determinant(matrix);
	if (determn == 0)
		return (NULL);
	inversed = new_matrix(matrix->size, NULL);
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
