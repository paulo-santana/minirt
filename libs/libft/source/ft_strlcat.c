/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:59:04 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:53:29 by fbafica          ###   ########.fr       */
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

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	counter;
	size_t	length;

	counter = 0;
	length = 0;
	while (dest[counter] && counter < size)
		++counter;
	while ((src[length]) && ((counter + length + 1) < size))
	{
		dest[counter + length] = src[length];
		++length;
	}
	if (counter != size)
		dest[counter + length] = '\0';
	return (counter + get_len(src));
}
