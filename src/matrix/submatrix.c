/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:58:47 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 21:10:55 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	*submatrix(t_matrix *a, int row, int col)
{
	int			i;
	int			j;
	t_matrix	*result;

	result = new_matrix(a->size - 1, NULL);
	i = 0;
	while (i < result->size)
	{
		j = 0;
		while (j < result->size)
		{
			result->data[i][j] = a->data[i + (i >= row)][j + (j >= col)];
			j++;
		}
		i++;
	}
	return (result);
}
