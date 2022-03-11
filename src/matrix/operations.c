/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:27:02 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 19:27:28 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

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
