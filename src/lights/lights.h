/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:59:14 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/15 13:01:53 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include <stdlib.h>
# include "structures.h"

t_point_light	*new_point_light(t_tuple *pos, t_color *intensity);
void			destroy_point_light(t_point_light *light);

#endif /* !LIGHT_H */
