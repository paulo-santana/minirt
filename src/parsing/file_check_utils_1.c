/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:10:33 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/13 19:38:15 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	count_identifiers(char **file_tokens, char *identifier)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (file_tokens[i])
	{
		tmp = ft_split(file_tokens[i], ' ');
		if (!ft_strcmp(tmp[0], identifier))
			++j;
		free_tokens(tmp);
		++i;
	}
	return (j);
}

int	get_line(char **file_tokens, char *identidier)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = 0;
	while (file_tokens[i])
	{
		tmp = ft_split(file_tokens[i], ' ');
		if (!ft_strcmp(*tmp, identidier))
			break ;
		free_tokens(tmp);
		tmp = NULL;
		++i;
	}
	if (tmp)
		free_tokens(tmp);
	return (i);
}

int	check_for_tab(char **file_tokens)
{
	int	i;

	i = 0;
	while (file_tokens[i])
	{
		if (ft_strchr(file_tokens[i], '\t'))
			return (-1);
		++i;
	}
	return (0);
}

char	**tokenize_line(char *line)
{
	char	*tmp_line;
	char	**line_tokens;

	tmp_line = ft_strdup(line);
	space_handler(&tmp_line);
	line_tokens = ft_split(tmp_line, ' ');
	free(tmp_line);
	return (line_tokens);
}
