/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:08:00 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/12 13:17:24 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "matrix.h"

t_matrix	*translation(double x, double y, double z)
{
	double	data[4][4];

	ft_bzero(data, sizeof(double) * 4 * 4);
	data[0][3] = x;
	data[1][3] = y;
	data[2][3] = z;
	data[3][3] = 1;
	data[2][2] = 1;
	data[1][1] = 1;
	data[0][0] = 1;
	return (new_matrix(4, data));
}

t_matrix	*scaling(double x, double y, double z)
{
	return (new_matrix(4, (double [4][4]){
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1},
	}));
}

t_matrix	*rotation_x(double rad)
{
	return (new_matrix(4, (double [4][4]){
		{1, 0, 0, 0},
		{0, cosf(rad), -sinf(rad), 0},
		{0, sinf(rad), cosf(rad), 0},
		{0, 0, 0, 1},
	}));
}

t_matrix	*rotation_y(double rad)
{
	return (new_matrix(4, (double [4][4]){
		{cosf(rad), 0, sinf(rad), 0},
		{0, 1, 0, 0},
		{-sinf(rad), 0, cosf(rad), 0},
		{0, 0, 0, 1},
	}));
}

t_matrix	*rotation_z(double rad)
{
	return (new_matrix(4, (double [4][4]){
		{cosf(rad), -sinf(rad), 0, 0},
		{sinf(rad), cosf(rad), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	}));
}
