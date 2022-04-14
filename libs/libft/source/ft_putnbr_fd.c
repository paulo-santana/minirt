/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:26:58 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:52:42 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_factor(int n)
{
	int	factor;

	factor = 1;
	while (n > 9)
	{
		n /= 10;
		factor *= 10;
	}
	return (factor);
}

static	void	write_not_exception(int n, int fd)
{
	int		factor;
	char	c;

	factor = get_factor(n);
	while (factor > 0)
	{
		c = (n / factor) + '0';
		write (fd, &c, 1);
		n = n % factor;
		factor /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		n *= -1;
		write (fd, "-", 1);
		write_not_exception(n, fd);
	}
	else if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	else
	{
		write_not_exception(n, fd);
	}
}
