/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:39:08 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:53:52 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

static	int	get_match(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	size_t	k;

	i = 0;
	while (big[i] != '\0' && i < len)
	{
		k = i;
		j = 0;
		while (little[j] != '\0' && k < len)
		{
			if (big[k] == little[j])
			{
				++k;
				++j;
			}
			else
				break ;
		}
		if (little[j] == '\0')
			return (k);
		++i;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	match;

	if (little[0] == '\0')
		return ((char *)big);
	match = get_match(big, little, len);
	if (match > 0)
		return ((char *)big + (match - get_len(little)));
	else
		return ((char *) '\0');
}
