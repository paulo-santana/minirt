/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 03:18:12 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:24:53 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "ray/ray.h"
#include "structures.h"
#include "tuple/tuple.h"

t_shape	*new_cylinder(void)
{
	t_shape	*cylinder;

	cylinder = new_shape();
	cylinder->cylinder_props.radius = 1;
	cylinder->cylinder_props.position.w = 1;
	cylinder->cylinder_props.min = 1;
	cylinder->cylinder_props.max = 2;
	cylinder->intersect = cylinder_intersect;
	cylinder->normal_at = cylinder_normal_at;
	cylinder->destroy_fn = destroy_cylinder;
	return (cylinder);
}
