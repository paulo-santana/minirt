NAME = miniRT

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

IFLAGS = -I ./src

HEADERS =  src/structures.h
HEADERS += src/minirt.h
HEADERS += src/tuple/tuple.h
HEADERS += src/shapes/shapes.h
HEADERS += src/lights/lights.h
HEADERS += src/utils/utils.h
HEADERS += libft/libft.h

COMMON_FILES += tuple/tuple_check.c
COMMON_FILES += tuple/tuple_creation.c
COMMON_FILES += tuple/tuple_operations.c
COMMON_FILES += tuple/vector_utils.c
COMMON_FILES += tuple/color_utils.c

COMMON_FILES += parsing/error_message.c
COMMON_FILES += parsing/file_check.c
COMMON_FILES += parsing/file_check_for_a.c
COMMON_FILES += parsing/file_check_for_c.c
COMMON_FILES += parsing/file_check_for_cy.c
COMMON_FILES += parsing/file_check_for_pl.c
COMMON_FILES += parsing/file_check_for_sp.c
COMMON_FILES += parsing/load_file.c
COMMON_FILES += parsing/tokens_utils_1.c
COMMON_FILES += parsing/file_check_utils_3.c

MANDATORY_FILES = parsing/file_check_utils_1.c
MANDATORY_FILES += parsing/file_check_utils_2.c
MANDATORY_FILES += parsing/list_utils_1.c
MANDATORY_FILES += parsing/file_check_for_l.c

BONUS_FILES = parsing/file_check_utils_1_bonus.c
BONUS_FILES += parsing/file_check_for_l_bonus.c
BONUS_FILES += parsing/list_utils_1_bonus.c
BONUS_FILES += parsing/file_check_utils_2_bonus.c

COMMON_FILES += matrix/creation.c
COMMON_FILES += matrix/check.c
COMMON_FILES += matrix/operations.c
COMMON_FILES += matrix/determinant.c
COMMON_FILES += matrix/submatrix.c
COMMON_FILES += matrix/transform.c

COMMON_FILES += ray/ray.c
COMMON_FILES += ray/creation.c
COMMON_FILES += ray/intersections.c
COMMON_FILES += ray/intersect_world.c
COMMON_FILES += ray/transform.c

COMMON_FILES += shapes/shape.c
COMMON_FILES += shapes/material.c
COMMON_FILES += shapes/normal.c
COMMON_FILES += shapes/sphere.c
COMMON_FILES += shapes/plane.c
COMMON_FILES += shapes/cylinder.c
COMMON_FILES += shapes/cylinder_utils.c

COMMON_FILES += lights/lighting.c
COMMON_FILES += lights/lighting_utils.c
COMMON_FILES += lights/point_light.c

COMMON_FILES += world/world.c

COMMON_FILES += camera/camera.c
COMMON_FILES += camera/canvas.c
COMMON_FILES += camera/view.c

COMMON_FILES += utils/double_comparison.c

COMMON_FILES += hooks/hooks.c

COMMON_FILES += debug.c

SRC_DIR = ./src
OBJ_ROOT = ./obj
OBJ_DIRS += $(OBJ_ROOT)/parsing
OBJ_DIRS += $(OBJ_ROOT)/tuple
OBJ_DIRS += $(OBJ_ROOT)/utils
OBJ_DIRS += $(OBJ_ROOT)/matrix
OBJ_DIRS += $(OBJ_ROOT)/ray
OBJ_DIRS += $(OBJ_ROOT)/shapes
OBJ_DIRS += $(OBJ_ROOT)/lights
OBJ_DIRS += $(OBJ_ROOT)/world
OBJ_DIRS += $(OBJ_ROOT)/camera
OBJ_DIRS += $(OBJ_ROOT)/hooks

MANDATORY_OBJ = $(addprefix $(OBJ_ROOT)/, $(COMMON_FILES:.c=.o))
MANDATORY_OBJ += $(addprefix $(OBJ_ROOT)/, $(MANDATORY_FILES:.c=.o))

BONUS_OBJ = $(addprefix $(OBJ_ROOT)/, $(COMMON_FILES:.c=.o))
BONUS_OBJ += $(addprefix $(OBJ_ROOT)/, $(BONUS_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wconversion -g3 -I $(MLX_DIR) -I $(LIBFT_DIR) -I src #-fsanitize=address
LFLAGS = -lm -L $(MLX_DIR) -lmlx -lXext -lX11 -L $(LIBFT_DIR) -lft #-fsanitize=address

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_ROOT) $(OBJ_DIRS) $(MANDATORY_OBJ) $(OBJ_ROOT)/main.o
	$(CC) $(MANDATORY_OBJ) $(OBJ_ROOT)/main.o -o $(NAME) $(LFLAGS)

bonus: $(LIBFT) $(MLX) $(OBJ_ROOT) $(OBJ_DIRS) $(BONUS_OBJ) $(OBJ_ROOT)/main.o
	$(CC) $(BONUS_OBJ) $(OBJ_ROOT)/main.o -o $(NAME) $(LFLAGS)

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
TEST_SRC += tests/test_planes.c
TEST_SRC += tests/test_cylinders.c
TEST_SRC += tests/test_shapes.c
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
	./$(NAME) ./file.rt

#SOURCE = main.c \
	file_check.c file_check_for_a.c file_check_for_c.c file_check_for_l.c \
	file_check_for_sp.c file_check_for_pl.c file_check_for_cy.c \
	file_check_utils_1.c file_check_utils_2.c \
	error_message.c load_file.c tokens_utils_1.c list_utils_1.c \
