/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:36 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/10 10:13:40 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <minirt.h>
# include <structures.h>

t_shape		*new_shape(void);

t_shape		*new_sphere(void);
void		destroy_sphere(void *sphere);
void		set_transform(t_shape *sphere, t_matrix *t);

t_material	*new_material(void);
void		destroy_material(void *mat);

#endif /* !SHAPES_H */
