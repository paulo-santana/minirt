/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:53:08 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:53:17 by fbafica          ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	int		len;
	char	*new_string;

	len = get_len(s);
	new_string = malloc(len + 1);
	if (!new_string)
		return (NULL);
	while (*s)
	{
		*(new_string++) = *(s++);
	}
	*new_string = '\0';
	return (new_string - len);
}
