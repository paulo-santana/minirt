/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:49:08 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/16 18:09:57 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_material	*new_material(void)
{
	t_material	*material;

	material = malloc(sizeof(t_material));
	material->color = new_color(1, 1, 1);
	material->ambient = new_color(.1, .1, .1);
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200;
	return (material);
}

void	destroy_material(void *data)
{
	t_material	*mat;

	mat = data;
	free(mat->color);
	free(mat->ambient);
	free(mat);
}
