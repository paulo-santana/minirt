/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:21:31 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:53:48 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (i < (n - 1) && (s1[i] == s2[i]) && (s1[i] != '\0'))
		{
			++i;
		}
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
}
