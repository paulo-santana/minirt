/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:53:25 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 21:43:00 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

inline double	determinant(t_matrix *a)
{
	double	det;
	int		col;

	if (a->size == 2)
		det = a->data[0][0] * a->data[1][1] - a->data[0][1] * a->data[1][0];
	else
	{
		det = 0;
		col = 0;
		while (col < a->size)
		{
			det = det + a->data[0][col] * cofactor(a, 0, col);
			col++;
		}
	}
	return (det);
}

double	cofactor(t_matrix *a, int row, int col)
{
	double	min;

	min = minor(a, row, col);
	if ((row + col) % 2 != 0)
		min = -min;
	return (min);
}

double	minor(t_matrix *a, int row, int col)
{
	t_matrix	*sub;
	double		minor;

	sub = submatrix(a, row, col);
	minor = determinant(sub);
	free(sub);
	return (minor);
}
