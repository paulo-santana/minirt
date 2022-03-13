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

#include "matrix.h"

t_matrix	*translation(float x, float y, float z)
{
	return (new_matrix(4, (float [4][4]){
		{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1},
	}));
}

t_matrix	*scaling(float x, float y, float z)
{
	return (new_matrix(4, (float [4][4]){
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1},
	}));
}

t_matrix	*rotation_x(float rad)
{
	return (new_matrix(4, (float [4][4]){
		{1, 0, 0, 0},
		{0, cosf(rad), -sinf(rad), 0},
		{0, sinf(rad), cosf(rad), 0},
		{0, 0, 0, 1},
	}));
}

t_matrix	*rotation_y(float rad)
{
	return (new_matrix(4, (float [4][4]){
		{cosf(rad), 0, sinf(rad), 0},
		{0, 1, 0, 0},
		{-sinf(rad), 0, cosf(rad), 0},
		{0, 0, 0, 1},
	}));
}

t_matrix	*rotation_z(float rad)
{
	return (new_matrix(4, (float [4][4]){
		{cosf(rad), -sinf(rad), 0, 0},
		{sinf(rad), cosf(rad), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	}));
}
