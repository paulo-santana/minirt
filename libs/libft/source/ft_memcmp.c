/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:27:23 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:52:11 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = s1;
	ptr2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (i < (n - 1) && (ptr1[i] == ptr2[i]))
		{
			++i;
		}
		return (ptr1[i] - ptr2[i]);
	}
}
