/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 22:54:46 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:52:13 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr_dest;
	const char	*ptr_src;

	ptr_dest = dest;
	ptr_src = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*ptr_dest = *ptr_src;
		++ptr_dest;
		++ptr_src;
		--n;
	}
	return (dest);
}
