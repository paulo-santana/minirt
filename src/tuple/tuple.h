/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:17:07 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 10:40:51 by psergio-         ###   ########.fr       */
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

t_tuple	*new_tuple(double x, double y, double z, double w);
t_tuple	*new_point(double x, double y, double z);
t_tuple	*new_vector(double x, double y, double z);

t_tuple	*add_tuples(t_tuple *a, t_tuple *b);
t_tuple	*subtract_tuples(t_tuple *a, t_tuple *b);
t_tuple	*negate_tuple(t_tuple *a);
t_tuple	*multiply_scalar(t_tuple *tuple, double value);
t_tuple	*divide_scalar(t_tuple *tuple, double value);

double	magnitude(t_tuple *a);
t_tuple	*normalize(t_tuple *vector);
t_tuple	*cross(t_tuple *a, t_tuple *b);

t_color	*new_color(double red, double green, double blue);
t_color	*add_colors(t_color *a, t_color *b);
t_color	*subtract_colors(t_color *a, t_color *b);
t_color	*multiply_scalar_color(t_color *tuple, double value);
t_color	*multiply_colors(t_color *a, t_color *b);
double	dot(t_tuple *a, t_tuple *b);

t_tuple	*normal_at(t_shape *sphere, t_tuple *world_point);
t_tuple	*reflect(t_tuple *vector, t_tuple *normal);

#endif
