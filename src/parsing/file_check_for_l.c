/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_for_l.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:58:59 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/16 02:23:49 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers_bonus.h"

static void	update_parameters(char **tokens, t_parameters *p)
{
	t_scene_light_param	*light;

	light = malloc(sizeof(t_scene_light_param));
	light->l_light_point = malloc(sizeof(double) * 3);
	light->l_light_point[0] = (double) ft_atof(tokens[1]);
	light->l_light_point[1] = (double) ft_atof(tokens[3]);
	light->l_light_point[2] = (double) ft_atof(tokens[5]);
	light->l_britghness = (double) ft_atof(tokens[6]);
	light->l_color = malloc(sizeof(double) * 3);
	light->l_color[0] = (double) ft_atof(tokens[7]);
	light->l_color[1] = (double) ft_atof(tokens[9]);
	light->l_color[2] = (double) ft_atof(tokens[11]);
	light->next = NULL;
	add_scene_light_param(p, light);
}

static int	check_min_max(char **tokens)
{
	if (ft_atof(tokens[1]) < MIN_FLOAT || ft_atof(tokens[1]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[3]) < MIN_FLOAT || ft_atof(tokens[3]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[5]) < MIN_FLOAT || ft_atof(tokens[5]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[6]) < 0 || ft_atof(tokens[6]) > 1.0)
		return (-1);
	if (ft_atof(tokens[7]) < 0 || ft_atof(tokens[7]) > 255)
		return (-1);
	if (ft_atof(tokens[9]) < 0 || ft_atof(tokens[9]) > 255)
		return (-1);
	if (ft_atof(tokens[11]) < 0 || ft_atof(tokens[11]) > 255)
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
	if (check_if_digit(tokens[7]) == -1)
		return (-1);
	if (check_if_digit(tokens[9]) == -1)
		return (-1);
	if (check_if_digit(tokens[11]) == -1)
		return (-1);
	return (0);
}

static int	validate_line(char **tokens)
{
	if (get_tokens_len(tokens) != 12)
		return (send_error("Error\nL parameter: Bad number of elements"));
	if (ft_strcmp(tokens[2], ",") || ft_strcmp(tokens[4], ",") || \
	ft_strcmp(tokens[8], ",") || ft_strcmp(tokens[10], ","))
		return (send_error("Error\nL parameter: Bad comma"));
	if (check_digit(tokens) == -1)
		return (send_error("Error\nL parameter: Bad digit"));
	if (check_min_max(tokens) == -1)
		return (send_error("Error\nL parameter: Bad min or max"));
	return (0);
}

int	check_for_l(char **file_tokens, t_parameters *p)
{
	char	**tokens;
	int		line_index;
	char	status;

	status = 0;
	if (count_identifiers(file_tokens, "L") != 1)
		return (send_error("Error\nL parameter: It must be one L"));
	line_index = get_line(file_tokens, "L");
	while (line_index < get_tokens_len(file_tokens))
	{
		tokens = tokenize_line(file_tokens[line_index]);
		if (validate_line(tokens) == -1)
			status = -1;
		else
			update_parameters(tokens, p);
		++line_index;
		line_index += get_line(file_tokens + line_index, "L");
		free_tokens(tokens);
	}
	return (status);
}
