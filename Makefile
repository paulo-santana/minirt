NAME = miniRT

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

IFLAGS = -I ./src

HEADERS =  src/minirt.h
HEADERS += src/tuple/tuple.h
HEADERS += src/utils/utils.h


SRC_FILES =  tuple/tuple_check.c
SRC_FILES += tuple/tuple_creation.c
SRC_FILES += tuple/tuple_operations.c
SRC_FILES += tuple/vector_utils.c
SRC_FILES += tuple/color_utils.c
SRC_FILES += matrix/creation.c
SRC_FILES += matrix/check.c
SRC_FILES += matrix/operations.c
SRC_FILES += matrix/determinant.c
SRC_FILES += matrix/submatrix.c
SRC_FILES += matrix/transform.c
SRC_FILES += ray/ray.c
SRC_FILES += ray/creation.c
SRC_FILES += ray/intersections.c
SRC_FILES += utils/float_comparison.c
SRC_FILES += debug.c

SRC_DIR = ./src
OBJ_ROOT = ./obj
OBJ_DIRS += $(OBJ_ROOT)/tuple
OBJ_DIRS += $(OBJ_ROOT)/utils
OBJ_DIRS += $(OBJ_ROOT)/matrix
OBJ_DIRS += $(OBJ_ROOT)/ray

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_ROOT)/, $(SRC_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -I $(MLX_DIR) -I src
LFLAGS = -lm -L $(MLX_DIR) -lmlx -lXext -lX11

RM = rm -rf

all: $(NAME)

$(NAME): $(MLX) $(OBJ_DIRS) $(OBJ) $(OBJ_ROOT)/main.o
	$(CC) $(OBJ) $(OBJ_ROOT)/main.o -o $(NAME) $(LFLAGS)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ_ROOT):
	mkdir -p $(OBJ_ROOT)

$(OBJ_ROOT)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

TEST_SRC += tests/munit/munit.c
TEST_SRC += tests/main.c
TEST_SRC += tests/tuples_test.c
TEST_SRC += tests/matrix_test.c
TEST_SRC += tests/matrix_transform_test.c
TEST_SRC += tests/ray_test.c

test: $(OBJ_ROOT) $(OBJ)
	$(CC) -g $(TEST_SRC) $(OBJ) -I src -o ./test_bin -lm
	./test_bin

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OBJ_ROOT)
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)
