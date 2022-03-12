/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:56:50 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/12 13:17:24 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include <stdlib.h>
# include "../structures.h"

typedef struct s_matrix {
	int		size;
	float	data[4][4];
}	t_matrix;

t_matrix	*identity_matrix(void);
t_matrix	*new_matrix(int size, float initial_values[4][4]);

int			matrix_equals(t_matrix *a, t_matrix *b);
int			is_invertible(t_matrix *a);

t_matrix	*matrix_multiply(t_matrix *a, t_matrix *b);
t_tuple		*matrix_multiply_tuple(t_matrix *a, t_tuple *b);
t_matrix	*transpose(t_matrix *matrix);

float		determinant(t_matrix *a);
float		minor(t_matrix *a, int row, int col);
float		cofactor(t_matrix *a, int row, int col);
t_matrix	*inverse(t_matrix *matrix);

t_matrix	*submatrix(t_matrix *a, int row, int col);

t_matrix	*translation(float x, float y, float z);
t_matrix	*scaling(float x, float y, float z);

#endif /* !MATRIX_H */
