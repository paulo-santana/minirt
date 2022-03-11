/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:26:34 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 13:58:41 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix44	*matrix44(float initial_values[4][4])
{
	int			i;
	int			j;
	t_matrix44	*matrix;

	i = 0;
	matrix = malloc(sizeof(t_matrix44));
	if (initial_values == NULL)
		return (matrix);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix->data[i][j] = initial_values[i][j];
			j++;
		}
		i++;
	}
	return (matrix);
}

t_matrix33	*matrix33(float initial_values[3][3])
{
	int			i;
	int			j;
	t_matrix33	*matrix;

	i = 0;
	matrix = malloc(sizeof(t_matrix33));
	if (initial_values == NULL)
		return (matrix);
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			matrix->data[i][j] = initial_values[i][j];
			j++;
		}
		i++;
	}
	return (matrix);
}

t_matrix22	*matrix22(float initial_values[2][2])
{
	int			i;
	int			j;
	t_matrix22	*matrix;

	i = 0;
	matrix = malloc(sizeof(t_matrix22));
	if (initial_values == NULL)
		return (matrix);
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			matrix->data[i][j] = initial_values[i][j];
			j++;
		}
		i++;
	}
	return (matrix);
}
