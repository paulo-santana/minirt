/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 03:14:22 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:15:21 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix/matrix.h"
#include "ray.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "tuple/tuple.h"

t_intersections	*new_intersections_list(void)
{
	t_intersections	*intersections;

	intersections = malloc(sizeof(t_intersections));
	intersections->count = 0;
	intersections->size = 50;
	intersections->is_sorted = 0;
	intersections->intersections = malloc(sizeof(t_intersection *) * 50);
	return (intersections);
}

void	destroy_intersections_list(t_intersections *inters)
{
	while (inters->count--)
		free(inters->intersections[inters->count]);
	free(inters->intersections);
	free(inters);
}
