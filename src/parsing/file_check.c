/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:55:34 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/14 19:24:53 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	file_check(char *file_name, t_parameters *p)
{
	char	**file_tokens;
	int		status;

	status = 0;
	if (ft_strcmp(ft_strrchr(file_name, '.'), ".rt") != 0)
		return (send_error("Error\nBad extension"));
	else if (load_file(file_name, &file_tokens) == -1)
		return (send_error("Error\nCould not open the file"));
	else if (check_for_tab(file_tokens) == -1 || \
	check_for_invalid_line(file_tokens) == -1)
		status = -1;
	else if (check_for_a(file_tokens, p) == -1)
		status = -1;
	else if (check_for_c(file_tokens, p) == -1)
		status = -1;
	else if (check_for_l(file_tokens, p) == -1)
		status = -1;
	else if (check_for_sp(file_tokens, p) == -1)
		status = -1;
	else if (check_for_pl(file_tokens, p) == -1)
		status = -1;
	else if (check_for_cy(file_tokens, p) == -1)
		status = -1;
	free_tokens(file_tokens);
	return (status);
}
