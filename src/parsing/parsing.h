/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:01:39 by fbafica           #+#    #+#             */
/*   Updated: 2022/04/19 03:28:30 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define MAX_FLOAT 340282346638528859811704183484516925440.0000000000000000
# define MIN_FLOAT -340282346638528859811704183484516925440.0000000000000000
# include "libft.h"
# include "structures.h"
# include <fcntl.h>
# include <stdlib.h>

int			file_check(char *file_name, t_parameters *p);
int			load_file(char *file_name, char ***tokens);
int			send_error(char *error_message);
int			check_start(char **file_tokens);
int			check_invalid_line(char **file_tokens);
int			check_for_a(char **file_tokens, t_parameters *p);
int			check_for_c(char **file_tokens, t_parameters *p);
int			check_for_l(char **file_tokens, t_parameters *p);
int			check_for_sp(char **file_tokens, t_parameters *p);
int			check_for_pl(char **file_tokens, t_parameters *p);
int			check_for_cy(char **file_tokens, t_parameters *p);
int			check_tab(char **file_tokens);
void		free_tokens(char **tokens);
void		print_tokens(char **tokens);
int			get_tokens_len(char **tokens);
int			count_identifiers(char **tokens, char *identifier);
int			get_line(char **tokens, char *identidier);
void		space_handler(char **input);
char		**tokenize_line(char *line);
int			check_if_digit(char *token);
int			check_normalized(char *x, char *y, char *z);
void		init_allocated_parameters(t_parameters *p);
void		free_allocated_parameters(t_parameters *p);
void		free_scene_object_param(t_scene_object_param *head);
void		free_scene_light_param(t_scene_light_param *head);
void		add_scene_object_param(t_parameters *p, t_scene_object_param *node);
void		add_scene_light_param(t_parameters *p, t_scene_light_param *node);

#endif
