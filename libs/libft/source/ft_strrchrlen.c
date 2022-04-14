/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchrlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:19:05 by fbafica           #+#    #+#             */
/*   Updated: 2021/11/30 16:20:39 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_len(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		++s;
		++i;
	}
	return (i);
}

int	ft_strrchrlen(const char *s, int c)
{
	int	len;
	int	i;
	int	j;
	int	ii;

	len = get_len(s);
	i = 0;
	j = 0;
	ii = 0;
	while (i <= len)
	{
		if (s[i] == (unsigned char)c)
		{
			j = i;
			ii = 1;
		}
		++i;
	}
	if (ii == 0)
		return (ii);
	else
		return (j);
}
