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

t_matrix22	*submatrix22(t_matrix33 *a, int row, int col)
{
	int			i;
	int			j;
	t_matrix22	*result;

	result = matrix22(NULL);
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			result->data[i][j] = a->data[i + (i >= row)][j + (j >= col)];
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix33	*submatrix33(t_matrix44 *a, int row, int col)
{
	int			i;
	int			j;
	t_matrix33	*result;

	result = matrix33(NULL);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result->data[i][j] = a->data[i + (i >= row)][j + (j >= col)];
			j++;
		}
		i++;
	}
	return (result);
}
