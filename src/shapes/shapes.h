/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:36 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 21:06:12 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <minirt.h>
# include <structures.h>

t_sphere	*new_sphere(void);
void		destroy_sphere(t_sphere *sphere);
void		set_transform(t_sphere *sphere, t_matrix *t);

t_material	*new_material(void);
void		destroy_material(t_material *mat);

#endif /* !SHAPES_H */
