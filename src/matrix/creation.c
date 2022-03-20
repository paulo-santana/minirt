/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:26:34 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 20:07:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "matrix.h"

t_matrix	*identity_matrix(void)
{
	int			i;
	int			j;
	t_matrix	*matrix;

	i = 0;
	matrix = malloc(sizeof(t_matrix));
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix->data[i][j] = 0;
			if (i == j)
				matrix->data[i][j] = 1;
			j++;
		}
		i++;
	}
	matrix->size = 4;
	return (matrix);
}

t_matrix	*new_matrix(int size, double initial_values[4][4])
{
	t_matrix	*matrix;

	matrix = malloc(sizeof(t_matrix));
	matrix->size = size;
	if (initial_values == NULL)
		return (matrix);
	ft_memcpy(matrix->data, initial_values, sizeof(double) * 16);
	return (matrix);
}
