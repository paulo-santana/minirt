/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:05:36 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/14 12:06:11 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <minirt.h>
# include <structures.h>

t_sphere	*new_sphere(t_tuple *position, float radius);
void		destroy_sphere(t_sphere *sphere);
void		set_transform(t_sphere *sphere, t_matrix *t);

#endif /* !SHAPES_H */
