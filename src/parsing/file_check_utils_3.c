/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:29:29 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/18 03:38:46 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minirt.h"

int	check_normalized(char *x, char *y, char *z)
{
	t_tuple	*vector;
	double	mag;

	vector = new_vector(ft_atof(x), ft_atof(y), ft_atof(z));
	mag = magnitude(vector);
	free(vector);
	if (fabs(mag - 1.0000) > 0.00001)
		return (-1);
	return (0);
}

int	check_start(char **file_tokens)
{
	int	i;
	int	status;

	i = 0;
	while (file_tokens[i])
	{
		if (*(file_tokens[i]) == ' ')
		{
			status = send_error("Error\nLine can't start with space");
			break ;
		}
		else
			status = 0;
		++i;
	}
	return (status);
}
