/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_for_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:14:55 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/16 23:24:56 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	update_parameters(char **tokens, t_parameters *p)
{
	p->a_lighting = (double) ft_atof(tokens[1]);
	p->a_color = malloc(sizeof(double) * 3);
	p->a_color[0] = (double) ft_atof(tokens[2]) / 255.0;
	p->a_color[1] = (double) ft_atof(tokens[4]) / 255.0;
	p->a_color[2] = (double) ft_atof(tokens[6]) / 255.0;
}

static int	check_min_max(char **tokens)
{
	if (ft_atoi(tokens[2]) < 0 || ft_atoi(tokens[2]) > 255)
		return (-1);
	if (ft_atoi(tokens[4]) < 0 || ft_atoi(tokens[4]) > 255)
		return (-1);
	if (ft_atoi(tokens[6]) < 0 || ft_atoi(tokens[6]) > 255)
		return (-1);
	return (0);
}

static int	check_digit(char **tokens)
{
	if (check_if_digit(tokens[1]) == -1)
		return (-1);
	if (check_if_digit(tokens[2]) == -1)
		return (-1);
	if (check_if_digit(tokens[4]) == -1)
		return (-1);
	if (check_if_digit(tokens[6]) == -1)
		return (-1);
	return (0);
}

static int	validate_line(char **tokens)
{
	if (get_tokens_len(tokens) != 7)
		return (send_error("Error\nA parameter: Bad number of elements"));
	if (ft_strcmp(tokens[3], ",") || ft_strcmp(tokens[5], ","))
		return (send_error("Error\nA parameter: Bad comma"));
	if (check_digit(tokens) == -1)
		return (send_error("Error\nA parameter: Bad digit"));
	if (check_min_max(tokens) == -1)
		return (send_error("Error\nA parameter: Bad min or max"));
	return (0);
}

int	check_for_a(char **file_tokens, t_parameters *p)
{
	char	**tokens;
	char	status;

	status = 0;
	if (count_identifiers(file_tokens, "A") != 1)
		return (send_error("Error\nA parameter: It must be one A"));
	tokens = tokenize_line(file_tokens[get_line(file_tokens, "A")]);
	if (validate_line(tokens) == -1)
		status = -1;
	else
		update_parameters(tokens, p);
	free_tokens(tokens);
	return (status);
}
