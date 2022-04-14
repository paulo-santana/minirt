/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:13:51 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:51:58 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = '\0';
		++ptr;
		--n;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;

	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	bzero(p, nmemb * size);
	return ((void *)p);
}
