/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:01:39 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/13 21:05:49 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H
# define MAX_FLOAT 340282346638528859811704183484516925440.0000000000000000
# define MIN_FLOAT -340282346638528859811704183484516925440.0000000000000000
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_scene_object_param
{
	char							*identifier;
	double							*cordinates;
	double							*color;
	double							*orientation_vector;
	double							diameter;
	double							height;
	struct s_scene_object_param		*next;
}	t_scene_object_param;

typedef struct s_parameters
{
	double					a_lighting;
	double					*a_color;
	double					*c_view_point;
	double					*c_orientation_vector;
	double					c_fov;
	double					*l_light_point;
	double					l_britghness;
	double					*l_color;
	t_scene_object_param	*object_head;
}	t_parameters;

				/*
				* FILE PARSER 
				*/
int			file_check(char *file_name, t_parameters *p);
int			load_file(char *file_name, char ***tokens);
int			send_error(char *error_message);
int			check_for_tab(char **tokens);
int			check_for_a(char **file_tokens, t_parameters *p);
int			check_for_c(char **file_tokens, t_parameters *p);
int			check_for_l(char **file_tokens, t_parameters *p);
int			check_for_sp(char **file_tokens, t_parameters *p);
int			check_for_pl(char **file_tokens, t_parameters *p);
int			check_for_cy(char **file_tokens, t_parameters *p);
void		free_tokens(char **tokens);
void		print_tokens(char **tokens);
int			get_tokens_len(char **tokens);
int			count_identifiers(char **tokens, char *identifier);
int			get_line(char **tokens, char *identidier);
void		space_handler(char **input);
char		**tokenize_line(char *line);
int			check_if_digit(char *token);
void		init_allocated_parameters(t_parameters *p);
void		free_allocated_parameters(t_parameters *p);
void		free_scene_object_param(t_scene_object_param *head);
void		add_scene_object_param(t_parameters *p, t_scene_object_param *node);

#endif