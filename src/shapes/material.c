/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:49:08 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 21:05:47 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_material	*new_material(void)
{
	t_material	*material;

	material = malloc(sizeof(t_material));
	material->color = new_color(1, 1, 1);
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200;
	return (material);
}

void	destroy_material(t_material *mat)
{
	free(mat->color);
	free(mat);
}
