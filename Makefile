NAME = miniRT

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

IFLAGS = -I ./src

HEADERS =  src/structures.h
HEADERS =  src/minirt.h
HEADERS += src/tuple/tuple.h
HEADERS += src/shapes/shapes.h
HEADERS += src/lights/lights.h
HEADERS += src/utils/utils.h
HEADERS += libft/libft.h

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
SRC_FILES += ray/intersect_world.c
SRC_FILES += ray/transform.c

SRC_FILES += shapes/material.c
SRC_FILES += shapes/sphere.c

SRC_FILES += lights/lighting.c
SRC_FILES += lights/point_light.c

SRC_FILES += world/world.c

SRC_FILES += camera/camera.c
SRC_FILES += camera/canvas.c
SRC_FILES += camera/view.c

SRC_FILES += utils/double_comparison.c

SRC_FILES += debug.c

SRC_DIR = ./src
OBJ_ROOT = ./obj
OBJ_DIRS += $(OBJ_ROOT)/tuple
OBJ_DIRS += $(OBJ_ROOT)/utils
OBJ_DIRS += $(OBJ_ROOT)/matrix
OBJ_DIRS += $(OBJ_ROOT)/ray
OBJ_DIRS += $(OBJ_ROOT)/shapes
OBJ_DIRS += $(OBJ_ROOT)/lights
OBJ_DIRS += $(OBJ_ROOT)/world
OBJ_DIRS += $(OBJ_ROOT)/camera

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_ROOT)/, $(SRC_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wconversion -g3 -I $(MLX_DIR) -I $(LIBFT_DIR) -I src #-fsanitize=address
LFLAGS = -lm -L $(MLX_DIR) -lmlx -lXext -lX11 -L $(LIBFT_DIR) -lft #-fsanitize=address

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_ROOT) $(OBJ_DIRS) $(OBJ) $(OBJ_ROOT)/main.o
	$(CC) $(OBJ) $(OBJ_ROOT)/main.o -o $(NAME) $(LFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

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
TEST_SRC += tests/test_tuples.c
TEST_SRC += tests/test_matrix.c
TEST_SRC += tests/test_matrix_transform.c
TEST_SRC += tests/test_ray.c
TEST_SRC += tests/test_sphere.c
TEST_SRC += tests/test_lights.c
TEST_SRC += tests/test_materials.c
TEST_SRC += tests/test_world.c
TEST_SRC += tests/test_camera.c
TEST_SRC += tests/utils.c

test: $(LIBFT) $(OBJ_DIRS) $(OBJ)
	$(CC) -g $(TEST_SRC) $(OBJ) -I src -o ./test_bin -lm -L$(LIBFT_DIR) -lft
	./test_bin # || ./test_bin --no-fork

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(OBJ_ROOT)
	$(RM) ./vgcore.*
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)
