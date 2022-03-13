/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:04:58 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/13 13:30:06 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stdlib.h>
# include "structures.h"

typedef struct s_ray {
	t_tuple	*origin;
	t_tuple	*direction;
}	t_ray;

t_ray	*new_ray(t_tuple *origin, t_tuple *direction);

t_tuple	*position(t_ray *ray, float t);

#endif /* !RAY_H */