/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 22:52:20 by fbafica           #+#    #+#             */
/*   Updated: 2021/06/14 21:23:39 by fbafica          ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
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
		return ((char *) '\0');
	else
		return ((char *)s + i);
}
