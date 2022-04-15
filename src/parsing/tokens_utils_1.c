/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 19:27:28 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/12 11:52:43 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_tokens_len(char **tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		++i;
		++tokens;
	}
	return (i);
}

void	print_tokens(char **tokens)
{
	int	i;
	int	len;

	i = 0;
	len = get_tokens_len(tokens);
	while (i < len)
	{
		ft_putendl_fd(tokens[i], 1);
		++i;
	}
}

void	free_tokens(char **tokens)
{
	int	i;
	int	len;

	if (!tokens)
		return ;
	i = 0;
	len = get_tokens_len(tokens);
	while (i < len)
	{
		free(tokens[i]);
		++i;
	}
	if (tokens)
		free(tokens);
}
