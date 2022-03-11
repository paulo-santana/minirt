/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:56:50 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 19:36:20 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include <stdlib.h>

typedef struct s_matrix44 {
	float	data[4][4];
}	t_matrix44;

typedef struct s_matrix33 {
	float	data[3][3];
}	t_matrix33;

typedef struct s_matrix22 {
	float	data[2][2];
}	t_matrix22;

t_matrix44	*matrix44(float initial_values[4][4]);
t_matrix33	*matrix33(float initial_values[3][3]);
t_matrix22	*matrix22(float initial_values[2][2]);

int			matrix44_equals(t_matrix44 *a, t_matrix44 *b);
int			matrix33_equals(t_matrix33 *a, t_matrix33 *b);
int			matrix22_equals(t_matrix22 *a, t_matrix22 *b);

t_matrix44	*matrix44_multiply(t_matrix44 *a, t_matrix44 *b);

#endif /* !MATRIX_H */
