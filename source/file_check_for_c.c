/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_for_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:58:59 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/13 21:00:35 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void	update_a_parameters(char **tokens, t_parameters *p)
{
	p->c_view_point = malloc(sizeof(double) * 3);
	p->c_view_point[0] = (double) ft_atof(tokens[1]);
	p->c_view_point[1] = (double) ft_atof(tokens[3]);
	p->c_view_point[2] = (double) ft_atof(tokens[5]);
	p->c_orientation_vector = malloc(sizeof(double) * 3);
	p->c_orientation_vector[0] = (double) ft_atof(tokens[6]);
	p->c_orientation_vector[1] = (double) ft_atof(tokens[8]);
	p->c_orientation_vector[2] = (double) ft_atof(tokens[10]);
	p->c_fov = (double) ft_atof(tokens[11]);
}

static int	check_min_max(char **tokens)
{
	if (ft_atof(tokens[1]) < MIN_FLOAT || ft_atof(tokens[1]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[3]) < MIN_FLOAT || ft_atof(tokens[3]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[5]) < MIN_FLOAT || ft_atof(tokens[5]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[6]) < -1.0 || ft_atof(tokens[6]) > 1.0)
		return (-1);
	if (ft_atof(tokens[8]) < -1.0 || ft_atof(tokens[8]) > 1.0)
		return (-1);
	if (ft_atof(tokens[10]) < -1.0 || ft_atof(tokens[10]) > 1.0)
		return (-1);
	if (ft_atof(tokens[11]) < 0 || ft_atof(tokens[11]) > 180)
		return (-1);
	return (0);
}

static int	check_digit(char **tokens)
{
	if (check_if_digit(tokens[1]) == -1)
		return (-1);
	if (check_if_digit(tokens[3]) == -1)
		return (-1);
	if (check_if_digit(tokens[5]) == -1)
		return (-1);
	if (check_if_digit(tokens[6]) == -1)
		return (-1);
	if (check_if_digit(tokens[8]) == -1)
		return (-1);
	if (check_if_digit(tokens[10]) == -1)
		return (-1);
	if (check_if_digit(tokens[11]) == -1)
		return (-1);
	return (0);
}

static int	validate_line(char **tokens)
{
	if (get_tokens_len(tokens) != 12)
		return (send_error("Error\nC parameter: Bad number of elements"));
	if (ft_strcmp(tokens[2], ",") || ft_strcmp(tokens[4], ",") || \
	ft_strcmp(tokens[7], ",") || ft_strcmp(tokens[9], ","))
		return (send_error("Error\nC parameter: Bad comma"));
	if (check_digit(tokens) == -1)
		return (send_error("Error\nC parameter: Bad digit"));
	if (check_min_max(tokens) == -1)
		return (send_error("Error\nC parameter: Bad min or max"));
	return (0);
}

int	check_for_c(char **file_tokens, t_parameters *p)
{
	char	**tokens;
	char	status;

	status = 0;
	if (count_identifiers(file_tokens, "C") != 1)
		return (send_error("Error\nC parameter: It must be one C"));
	tokens = tokenize_line(file_tokens[get_line(file_tokens, "C")]);
	if (validate_line(tokens) == -1)
		status = -1;
	else
		update_a_parameters(tokens, p);
	free_tokens(tokens);
	return (status);
}
