/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:03:54 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:53:43 by fbafica          ###   ########.fr       */
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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*new_string;
	int		i;

	len = get_len(s);
	new_string = malloc(len + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_string[i] = f(i, s[i]);
		++i;
	}
	new_string[i] = '\0';
	return (new_string);
}
