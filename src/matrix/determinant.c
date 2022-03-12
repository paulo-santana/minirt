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

inline float	determinant22(t_matrix22 *a)
{
	return (a->data[0][0] * a->data[1][1] - a->data[0][1] * a->data[1][0]);
}

float	cofactor(t_matrix33 *a, int row, int col)
{
	float	minor;

	minor = minor33(a, row, col);
	if ((row + col) % 2 != 0)
		minor = -minor;
	return (minor);
}

float	determinant33(t_matrix33 *a)
{
	return (
		a->data[0][0] * cofactor(a, 0, 0)
		+ a->data[0][1] * cofactor(a, 0, 1)
		+ a->data[0][2] * cofactor(a, 0, 2)
		);
}

float	minor33(t_matrix33 *a, int row, int col)
{
	t_matrix22	*sub;
	float		minor;

	sub = submatrix22(a, row, col);
	minor = determinant22(sub);
	free(sub);
	return (minor);
}
