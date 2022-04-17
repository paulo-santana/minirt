/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:59:14 by psergio-          #+#    #+#             */
/*   Updated: 2022/04/16 01:56:12 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include <stdlib.h>
# include "structures.h"

typedef struct s_lighting_args {
	t_material		*material;
	t_point_light	*light;
	t_tuple			*position;
	t_tuple			*eye_vector;
	t_tuple			*normal_vector;
	int				in_shadow;
}	t_lighting_args;

t_point_light	*new_point_light(t_tuple *pos, t_color *intensity);
void			destroy_point_light(t_point_light *light);
t_color			*lighting(t_lighting_args *args);

t_color			*get_diffuse(
					t_lighting_args *args,
					t_color *effective_color,
					double light_dot_normal);
t_color			*get_brighter(t_color *a, t_color *b);
t_color			*get_ambient(t_lighting_args *args);

#endif /* !LIGHT_H */
