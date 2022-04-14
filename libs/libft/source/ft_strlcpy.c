/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:03:47 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:53:34 by fbafica          ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	while (!dst || !src)
		return (0);
	src_len = get_len(src);
	if (size == 0)
		return (src_len);
	while (size - 1 > 0 && *src != '\0')
	{
		*(dst++) = *(src++);
		--size;
	}
	*dst = '\0';
	return (src_len);
}
