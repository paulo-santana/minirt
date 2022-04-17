/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_for_cy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:58:59 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/17 20:56:19 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	update_parameters(char **tokens, t_parameters *p)
{
	t_scene_object_param	*object;

	object = malloc(sizeof(t_scene_object_param));
	object->identifier = ft_strdup("cy");
	object->cordinates = malloc(sizeof(double) * 3);
	object->cordinates[0] = (double) ft_atof(tokens[1]);
	object->cordinates[1] = (double) ft_atof(tokens[3]);
	object->cordinates[2] = (double) ft_atof(tokens[5]);
	object->orientation_vector = malloc(sizeof(double) * 3);
	object->orientation_vector[0] = (double) ft_atof(tokens[6]);
	object->orientation_vector[1] = (double) ft_atof(tokens[8]);
	object->orientation_vector[2] = (double) ft_atof(tokens[10]);
	object->color = malloc(sizeof(double) * 3);
	object->color[0] = (double) ft_atof(tokens[13]) / 255.0;
	object->color[1] = (double) ft_atof(tokens[15]) / 255.0;
	object->color[2] = (double) ft_atof(tokens[17]) / 255.0;
	object->diameter = (double) ft_atof(tokens[11]);
	object->height = (double) ft_atof(tokens[12]);
	object->next = NULL;
	add_scene_object_param(p, object);
}

static int	check_min_max(char **tokens)
{
	if (ft_atof(tokens[1]) < MIN_FLOAT || ft_atof(tokens[1]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[3]) < MIN_FLOAT || ft_atof(tokens[3]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[5]) < MIN_FLOAT || ft_atof(tokens[5]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[6]) < -1 || ft_atof(tokens[6]) > 1)
		return (-1);
	if (ft_atof(tokens[8]) < -1 || ft_atof(tokens[8]) > 1)
		return (-1);
	if (ft_atof(tokens[10]) < -1 || ft_atof(tokens[10]) > 1)
		return (-1);
	if (ft_atof(tokens[11]) < 0 || ft_atof(tokens[11]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[12]) < 0 || ft_atof(tokens[12]) > MAX_FLOAT)
		return (-1);
	if (ft_atof(tokens[13]) < 0 || ft_atof(tokens[13]) > 255)
		return (-1);
	if (ft_atof(tokens[15]) < 0 || ft_atof(tokens[15]) > 255)
		return (-1);
	if (ft_atof(tokens[17]) < 0 || ft_atof(tokens[17]) > 255)
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
	if (check_if_digit(tokens[12]) == -1)
		return (-1);
	if (check_if_digit(tokens[13]) == -1)
		return (-1);
	if (check_if_digit(tokens[15]) == -1)
		return (-1);
	if (check_if_digit(tokens[17]) == -1)
		return (-1);
	return (0);
}

static int	validate_line(char **tokens)
{
	if (get_tokens_len(tokens) != 18)
		return (send_error("Error\ncy parameter: Bad number of elements"));
	if (ft_strcmp(tokens[2], ",") || ft_strcmp(tokens[4], ",") || \
	ft_strcmp(tokens[7], ",") || ft_strcmp(tokens[9], ",") || \
	ft_strcmp(tokens[14], ",") || ft_strcmp(tokens[16], ","))
		return (send_error("Error\ncy parameter: Bad comma"));
	if (check_digit(tokens) == -1)
		return (send_error("Error\ncy parameter: Bad digit"));
	if (check_min_max(tokens) == -1)
		return (send_error("Error\ncy parameter: Bad min or max"));
	if (check_normalized(tokens[6], tokens[8], tokens[10]) == -1)
		return (send_error("Error\ncy parameter: Bad normalization"));
	return (0);
}

int	check_for_cy(char **file_tokens, t_parameters *p)
{
	char	**tokens;
	int		line_index;
	char	status;

	status = 0;
	if (count_identifiers(file_tokens, "cy") <= 0)
		return (send_error("Error\ncy parameter: It must be at least one cy"));
	line_index = get_line(file_tokens, "cy");
	while (line_index < get_tokens_len(file_tokens))
	{
		tokens = tokenize_line(file_tokens[line_index]);
		if (validate_line(tokens) == -1)
			status = -1;
		else
			update_parameters(tokens, p);
		++line_index;
		line_index += get_line(file_tokens + line_index, "cy");
		free_tokens(tokens);
	}
	return (status);
}
