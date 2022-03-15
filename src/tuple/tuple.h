/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:17:07 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 14:32:43 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include <math.h>
# include <stdlib.h>
# include "../structures.h"

int		is_point(t_tuple *tuple);
int		is_vector(t_tuple *tuple);
int		tuple_equals(t_tuple *a, t_tuple *b);

t_tuple	*new_tuple(float x, float y, float z, float w);
t_tuple	*new_point(float x, float y, float z);
t_tuple	*new_vector(float x, float y, float z);

t_tuple	*add_tuples(t_tuple *a, t_tuple *b);
t_tuple	*subtract_tuples(t_tuple *a, t_tuple *b);
t_tuple	*negate_tuple(t_tuple *a);
t_tuple	*multiply_scalar(t_tuple *tuple, float value);
t_tuple	*divide_scalar(t_tuple *tuple, float value);

float	magnitude(t_tuple *a);
t_tuple	*normalize(t_tuple *vector);
t_tuple	*cross(t_tuple *a, t_tuple *b);

t_color	*new_color(float red, float green, float blue);
t_color	*add_colors(t_color *a, t_color *b);
t_color	*subtract_colors(t_color *a, t_color *b);
t_color	*multiply_scalar_color(t_color *tuple, float value);
t_color	*multiply_colors(t_color *a, t_color *b);
float	dot(t_tuple *a, t_tuple *b);

t_tuple	*normal_at(t_sphere *sphere, t_tuple *world_point);
t_tuple	*reflect(t_tuple *vector, t_tuple *normal);

#endif
