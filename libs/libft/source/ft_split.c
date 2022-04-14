/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:27:23 by fbafica           #+#    #+#             */
/*   Updated: 2021/10/25 16:58:19 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	fill(char c, char const *s, char ***array)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			(*array)[j][k] = s[i];
			++k;
			if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			{
				++j;
				k = 0;
			}
		}
		++i;
	}
}

static	void	allocate(int rows, int *columns, char ***array)
{
	int	i;

	*array = malloc((rows + 1) * sizeof (char *));
	if (!*array)
		return ;
	(*array)[rows] = (char *) '\0';
	i = 0;
	while (i < rows)
	{
		(*array)[i] = malloc(columns[i] + 1);
		if (!(*array)[i])
			return ;
		(*array)[i][columns[i]] = '\0';
		++i;
	}
}

static	void	get_columns(char const *s, char c, int rows, int **columns)
{
	int	i;
	int	row_position;
	int	str_len;

	i = 0;
	row_position = 0;
	str_len = 0;
	*columns = malloc(rows * sizeof (int));
	if (!*columns)
		return ;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			++str_len;
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
		{
			(*columns)[row_position] = str_len;
			str_len = 0;
			++row_position;
		}
		++i;
	}
}

static	int	get_rows(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			++j;
		++i;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		rows;
	int		*columns;
	char	**array;

	rows = get_rows(s, c);
	get_columns(s, c, rows, &columns);
	allocate(rows, columns, &array);
	if (!array)
		return (NULL);
	fill(c, s, &array);
	free(columns);
	return (array);
}
