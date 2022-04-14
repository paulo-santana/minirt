/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:56:06 by fbafica           #+#    #+#             */
/*   Updated: 2021/06/15 23:56:37 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_multiple_signals(const char *nptr)
{
	int	i;
	int	j;
	int	ii;

	i = 0;
	j = 0;
	ii = 0;
	while (((nptr[i] == '\t') || (nptr[i] == '\n') || (nptr[i] == '\v')
			|| (nptr[i] == '\f') || (nptr[i] == '\r') || (nptr[i] == '\x1b')
			|| (nptr[i] == ' ')) && (nptr[i] != '\e'))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			++j;
		if (nptr[i] == '+')
			++ii;
		++i;
	}
	if ((j > 0 && ii > 0) || (j > 1 || ii > 1))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sig;
	int	concat;

	if (check_multiple_signals(nptr) == 1)
		return (0);
	i = 0;
	sig = 1;
	concat = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sig *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		concat = (nptr[i] - '0') + (concat * 10);
		i++;
	}
	return (concat * sig);
}
