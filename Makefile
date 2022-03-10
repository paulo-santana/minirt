NAME = miniRT

IFLAGS = -I ./src

HEADERS =  src/minirt.h
HEADERS += src/tuple/tuple.h
HEADERS += src/utils/utils.h


SRC_FILES =  tuple/tuple_check.c
SRC_FILES += tuple/tuple_creation.c
SRC_FILES += tuple/tuple_operations.c
SRC_FILES += utils/float_comparison.c

SRC_DIR = ./src
OBJ_ROOT = ./obj
OBJ_DIRS += $(OBJ_ROOT)/tuple
OBJ_DIRS += $(OBJ_ROOT)/utils

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_ROOT)/, $(SRC_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJ) $(OBJ_ROOT)/main.o
	$(CC) $(OBJ) $(OBJ_ROOT)/main.o -o $(NAME)

$(OBJ_DIRS): $(OBJ_ROOT)
	mkdir -p $@

$(OBJ_ROOT):
	mkdir -p $(OBJ_ROOT)

$(OBJ_ROOT)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

TEST_SRC += tests/munit/munit.c
TEST_SRC += tests/main.c

test: $(OBJ_ROOT) $(OBJ)
	$(CC) $(TEST_SRC) $(OBJ) -o ./test_bin
	./test_bin

clean:
	$(RM) $(OBJ_ROOT)

fclean: clean
	$(RM) $(NAME)

re: fclean all
