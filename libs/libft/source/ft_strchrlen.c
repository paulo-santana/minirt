/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:48:50 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/29 20:09:49 by fbafica          ###   ########.fr       */
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

int	ft_strchrlen(const char *s, int c)
{
	int	len;
	int	i;
	int	j;

	len = get_len(s);
	i = 0;
	j = 0;
	while (i <= len)
	{
		if (s[i] == (unsigned char)c)
		{
			++j;
			break ;
		}
		++i;
	}
	if (j == 0)
		return (j);
	else
		return (i);
}
