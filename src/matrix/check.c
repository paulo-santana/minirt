/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:55:54 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 18:57:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <minirt.h>

int	matrix44_equals(t_matrix44 *a, t_matrix44 *b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (!fequals(a->data[i][j], b->data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	matrix33_equals(t_matrix33 *a, t_matrix33 *b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (!fequals(a->data[i][j], b->data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	matrix22_equals(t_matrix22 *a, t_matrix22 *b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (!fequals(a->data[i][j], b->data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
