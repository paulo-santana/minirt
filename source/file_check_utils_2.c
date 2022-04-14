/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:19:51 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/13 17:40:01 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void	add_space(char **input, int index)
{
	char	*frst_half;
	char	*scnd_half;
	char	*tmp;

	if ((*input)[index + 1] != ' ' && (*input)[index + 1] != '\0')
		++index;
	tmp = ft_substr(*input, 0, index);
	frst_half = ft_strjoin(tmp, " ");
	free(tmp);
	scnd_half = ft_substr(*input, index, ft_strlen(*input) - index);
	tmp = ft_strdup(*input);
	free(*input);
	*input = ft_strjoin(frst_half, scnd_half);
	free(tmp);
	free(frst_half);
	free(scnd_half);
}

void	space_handler(char **input)
{
	char	*set;
	int		i;
	int		j;

	set = ",";
	i = 1;
	while ((*input)[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if ((((*input)[i - 1] != ' ' && \
			(*input)[i] == set[j]) || ((*input)[i + 1] != ' ' \
			&& (*input)[i + 1] != '\0' && (*input)[i] == set[j])))
			{
				add_space(input, i);
				++i;
				space_handler(input);
			}
			++j;
		}
		++i;
	}
}

int	check_if_digit(char *token)
{
	if (ft_strrchrlen(token, '.') > ft_strchrlen(token, '.'))
		return (-1);
	if (ft_strrchrlen(token, '+') > ft_strchrlen(token, '+'))
		return (-1);
	if (ft_strrchrlen(token, '-') > ft_strchrlen(token, '-'))
		return (-1);
	while (*token == '+' || *token == '-')
		++token;
	while (*token != '\0')
	{
		if (*token == '.')
			++token;
		if (!ft_isdigit(*token))
			return (-1);
		++token;
	}
	return (0);
}

void	init_allocated_parameters(t_parameters *p)
{
	p->a_color = NULL;
	p->c_view_point = NULL;
	p->c_orientation_vector = NULL;
	p->l_light_point = NULL;
	p->l_color = NULL;
	p->object_head = NULL;
}

void	free_allocated_parameters(t_parameters *p)
{
	if (p->a_color)
		free(p->a_color);
	if (p->c_view_point)
		free(p->c_view_point);
	if (p->c_orientation_vector)
		free(p->c_orientation_vector);
	if (p->l_light_point)
		free(p->l_light_point);
	if (p->l_color)
		free(p->l_color);
	if (p->object_head)
		free_scene_object_param(p->object_head);
	free(p);
}
