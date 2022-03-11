/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:09:48 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 10:01:49 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_tuple {
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_color {
	float	red;
	float	green;
	float	blue;
}	t_color;

#endif /* !STRUCTURES_H */
