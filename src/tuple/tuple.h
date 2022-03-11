/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:17:07 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 20:46:36 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include <math.h>
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

#endif
