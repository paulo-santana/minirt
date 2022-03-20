/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:08:31 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/12 12:10:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix/matrix.h"
#include "structures.h"
#include <stdio.h>

void	print_color(t_color *color)
{
	printf("\n");
	printf("red: %f\n", color->red);
	printf("green: %f\n", color->green);
	printf("blue: %f\n", color->blue);
}

void	print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			printf("%8.4f", matrix->data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_tuple(t_tuple *tuple)
{
	printf("x: %8.4f, y: %8.4f, z:%8.4f, w: %8.4f\n",
		tuple->x, tuple->y, tuple->z, tuple->w);
}
