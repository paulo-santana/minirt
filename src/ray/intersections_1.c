/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:45:23 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/19 03:14:43 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix/matrix.h"
#include "ray.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "tuple/tuple.h"
#include "utils/utils.h"

void	add_intersection(t_intersections *intersections, t_intersection *new)
{
	t_intersection	**arr;

	if (intersections->count >= intersections->size)
	{
		arr = malloc(sizeof(t_intersection *) * (intersections->size + 50));
		ft_memmove(arr, intersections->intersections, sizeof(t_intersection *)
			* (intersections->size));
		free(intersections->intersections);
		intersections->intersections = arr;
		intersections->size += 50;
	}
	intersections->intersections[intersections->count] = new;
	intersections->count++;
	intersections->is_sorted = 0;
}

t_intersection	*new_intersection(double t, void *obj, t_object_types obj_type)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
	i->t = t;
	i->object = obj;
	i->object_type = obj_type;
	return (i);
}

t_intersection	**intersection_arr(t_list *list)
{
	int				i;
	size_t			size;
	t_intersection	**inters;

	size = (size_t)ft_lstsize(list);
	inters = malloc(sizeof(t_intersection *) * size);
	i = 0;
	while (list)
	{
		inters[i] = list->content;
		list = list->next;
	}
	return (inters);
}

void	sort_intersections(t_intersections *inters)
{
	size_t			i;
	size_t			j;
	t_intersection	*tmp;

	if (inters->is_sorted)
		return ;
	i = 0;
	while (i < inters->count)
	{
		j = i + 1;
		while (j < inters->count)
		{
			if (inters->intersections[i]->t > inters->intersections[j]->t)
			{
				tmp = inters->intersections[i];
				inters->intersections[i] = inters->intersections[j];
				inters->intersections[j] = tmp;
			}
			j++;
		}
		i++;
	}
	inters->is_sorted = 1;
}

t_intersection	*hit(t_intersections *inters)
{
	size_t	i;

	if (!inters->is_sorted)
		sort_intersections(inters);
	i = 0;
	while (i < inters->count)
	{
		if (inters->intersections[i]->t > 0)
			return (inters->intersections[i]);
		i++;
	}
	return (NULL);
}
