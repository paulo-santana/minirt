/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 11:45:52 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:54:11 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		++i;
	}
	return (i);
}

static size_t	get_size(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	size;

	s_len = get_len(s);
	if (start >= s_len)
		size = 0;
	else if (len > (s_len - start))
		size = s_len - start;
	else
		size = len;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	size;
	size_t	i;

	size = get_size(s, start, len);
	if (!size || s == NULL)
		return (ft_calloc(1, 1));
	else
		substring = malloc((size + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < size)
	{
		substring[i] = s[i + start];
		++i;
	}
	substring[i] = '\0';
	return (substring);
}
