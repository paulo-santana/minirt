# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 21:48:51 by fbafica           #+#    #+#              #
#    Updated: 2022/04/11 22:37:23 by fbafica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

C_SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			ft_strcmp.c ft_strchrlen.c ft_strrchrlen.c ft_atof.c \

VPATH = ./source/

INCLUDES_PATH = ./includes/

OBJ_DIR = ./objects/

OBJ = $(C_SOURCES:%.c=$(OBJ_DIR)%.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rcs $@ $(OBJ)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(FLAGS) -c $^ -I$(INCLUDES_PATH) -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
