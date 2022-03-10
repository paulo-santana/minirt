NAME = miniRT

IFLAGS = -I ./src

HEADERS = src/minirt.h

SRC_FILES = main.c

SRC_DIR = ./src
OBJ_DIR = ./obj

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
