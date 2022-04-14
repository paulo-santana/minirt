/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:26:19 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/13 21:07:38 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	main(int argc, char **argv)
{
	t_parameters	*p;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nBad arguments", 2);
		return (1);
	}
	p = malloc(sizeof(t_parameters));
	init_allocated_parameters(p);
	if (file_check(argv[1], p) == -1)
		ft_putendl_fd("Erou!", 2);
	free_allocated_parameters(p);
	return (0);
}
