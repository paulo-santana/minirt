/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:18:56 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/12 23:01:17 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_decimals(const char *nptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (nptr[i])
	{
		++j;
		if (nptr[i] == '.')
			j = 0;
		++i;
	}
	if (i == j)
		return (0);
	return (j);
}

static char	*get_concat_str(const char *nptr)
{
	char	*concat;
	char	*tmp_1;
	char	*tmp_2;

	if (!ft_isdigit(*nptr))
		++nptr;
	if (!ft_strchr(nptr, '.'))
		return (ft_strdup(nptr));
	tmp_1 = ft_substr(nptr, 0, ft_strchrlen(nptr, '.'));
	tmp_2 = ft_substr(nptr, ft_strchrlen(nptr, '.') + 1, ft_strlen(nptr));
	concat = ft_strjoin(tmp_1, tmp_2);
	free(tmp_1);
	free(tmp_2);
	return (concat);
}

static float	get_sign(const char *nptr)
{
	float	sig;
	int		i;

	sig = 1.0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		++i;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sig *= -1.0;
		++i;
	}
	return (sig);
}

static	int	check_multiple_signals(const char *nptr)
{
	int	i;
	int	j;
	int	ii;

	i = 0;
	j = 0;
	ii = 0;
	while (((nptr[i] == '\t') || (nptr[i] == '\n') || (nptr[i] == '\v')
			|| (nptr[i] == '\f') || (nptr[i] == '\r') || (nptr[i] == '\x1b')
			|| (nptr[i] == ' ')) && (nptr[i] != '\e'))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			++j;
		if (nptr[i] == '+')
			++ii;
		++i;
	}
	if ((j > 0 && ii > 0) || (j > 1 || ii > 1))
		return (1);
	else
		return (0);
}

float	ft_atof(const char *nptr)
{
	float	sig;
	char	*concat_str;
	int		concat_nbr;
	int		decimals;
	float	base;

	if (check_multiple_signals(nptr) == 1)
		return (0);
	concat_str = get_concat_str(nptr);
	sig = get_sign(nptr);
	decimals = get_decimals(nptr);
	base = 1.0;
	while (decimals > 0)
	{
		base *= 10.0;
		--decimals;
	}
	concat_nbr = ft_atoi(concat_str);
	free(concat_str);
	return (concat_nbr / base * sig);
}
