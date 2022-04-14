/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 21:45:51 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:52:16 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*ptr_src;
	char	*ptr_dest;
	size_t	i;

	i = -1;
	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (ptr_src < ptr_dest)
		while ((int)(--len) >= 0)
			*(ptr_dest + len) = *(ptr_src + len);
	else
		while (++i < len)
			*(ptr_dest + i) = *(ptr_src + i);
	return (dest);
}
