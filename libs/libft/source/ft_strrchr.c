/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 23:17:19 by fbafica           #+#    #+#             */
/*   Updated: 2021/06/14 21:41:09 by fbafica          ###   ########.fr       */
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

char	*ft_strrchr(const char *s, int c)
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
		return ((char *) '\0');
	else
		return ((char *)s + j);
}
