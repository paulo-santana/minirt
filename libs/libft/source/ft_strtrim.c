/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:00:49 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:54:00 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_len(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

static	int	does_exist(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		++i;
	}
	return (0);
}

static	int	get_match_end(char const *s1, char const *set)
{
	int	i;

	i = get_len(s1) - 1;
	while (i > 0)
	{
		if (does_exist(set, s1[i]))
			--i;
		else
			break ;
	}
	return (i);
}

static	int	get_match_start(const char *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (does_exist(set, s1[i]))
			++i;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_string;
	int		start;
	int		end;
	int		size;
	int		i;

	start = get_match_start(s1, set);
	end = get_match_end(s1, set);
	if (start == get_len(s1))
		return (ft_calloc(1, 1));
	if (end - start < 0)
		size = (end - start + 2) * -1;
	else
		size = end - start + 2;
	new_string = malloc(size);
	if (!new_string)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		new_string[i] = s1[start + i];
		++i;
	}
	new_string[i] = '\0';
	return (new_string);
}
