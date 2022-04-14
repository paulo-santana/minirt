/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 19:49:52 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/10 20:55:35 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void	saved_update(char **buffer, char **saved)
{
	char	*tmp;

	tmp = ft_strjoin(*saved, *buffer);
	free(*saved);
	*saved = ft_strdup(tmp);
	free(tmp);
}

int	load_file(char *file_name, char ***tokens)
{
	int		fd;
	ssize_t	read_call;
	char	*buffer;
	char	*saved;

	fd = open(file_name, O_RDONLY);
	saved = ft_calloc(1, 1);
	buffer = malloc(100);
	read_call = read(fd, buffer, 99);
	while (read_call > 0)
	{
		buffer[read_call] = '\0';
		saved_update(&buffer, &saved);
		read_call = read(fd, buffer, 99);
	}
	free(buffer);
	if (fd == -1 || read_call == -1)
	{
		free(saved);
		return (-1);
	}
	*tokens = ft_split(saved, '\n');
	free(saved);
	return (0);
}
