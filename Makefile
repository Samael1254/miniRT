NAME = miniRT

SOURCES_DIR = srcs/
BONUS_DIR = srcs/
BUILD_DIR = build/
HEADERS_DIR = includes/

HEADERS = minirt.h minirt_defs.h
HEADERS := $(addprefix $(HEADERS_DIR), $(HEADERS))

SRCS_MAIN := main.c exit_program.c events.c init_state.c

SRCS_PARSING := init_scene.c insert_in_struct.c utils.c utils2.c objects_list.c \
				object_sphere.c object_plane.c object_cylinder.c utils_general_objects.c

SRCS_GRAPHICS := color.c graphics.c

SRCS_ERRORS := errors.c check_arguments.c

SRCS_RAYTRACING := raytracing.c intersections.c intersect_objects.c rays.c light.c \
				   normals.c

SOURCES := $(addprefix $(SOURCES_DIR)base/, $(SRCS_MAIN)) \
           $(addprefix $(SOURCES_DIR)parsing/, $(SRCS_PARSING)) \
           $(addprefix $(SOURCES_DIR)graphics/, $(SRCS_GRAPHICS)) \
           $(addprefix $(SOURCES_DIR)errors/, $(SRCS_ERRORS)) \
           $(addprefix $(SOURCES_DIR)raytracing/, $(SRCS_RAYTRACING)) \

OBJS := $(addprefix $(BUILD_DIR), $(notdir $(SOURCES:.c=.o)))

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I./libs/libft/includes -I./libs/mlx #-g

LIBFT = ./libs/libft/lib/libft.a

MLX = ./libs/mlx/libmlx.a

LIBFLAGS := -lft -Llibs/libft/lib -lmlx -Llibs/mlx -lX11 -lXext -lm

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(HEADERS)
	@ echo " \033[33mCompiling miniRT\033[m"
	@ $(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFLAGS)
	@ echo " \033[1;32m MiniRT binary compiled\033[m"

$(BUILD_DIR)%.o: $(SOURCES_DIR)*/%.c
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@ echo " \033[33mCompiling Libft\033[m"
	@ cd libs/libft && $(MAKE) -s -j
	@ tput cuu1 && tput el
	@ tput cuu1 && tput el
	@ echo " \033[34m Libft compiled\033[m"

$(MLX):
	@ echo " \033[33mCompiling MiniLibX\033[m"
	@ cd libs/mlx && $(MAKE) -s -j
	@ echo " \033[34m MiniLibX compiled\033[m"

fclean_libft:
	@ echo " \033[33mCleaning Libft\033[m"
	@ cd libs/libft && $(MAKE) -s fclean
	@ tput cuu1 && tput el
	@ tput cuu1 && tput el
	@ echo " \033[34m Libft cleaned\033[m"

libft: fclean_libft $(LIBFT)

check_norm:
	@ echo " \033[33mChecking norm\033[m"
	@ echo " \033[33m... norminette\033[m"
	@ norminette src > /dev/null 2>&1 && tput cuu1 && tput el && echo " \033[32m norminette valid\033[m" || (tput cuu1 && tput el && echo " \033[31m norminette check failed\033[m"; true)

all: $(NAME) check_norm

clean:
	@ echo " \033[33mCleaning\033[m"
	@ rm -f $(BUILD_DIR)/*.o
	@ rm -df $(BUILD_DIR)
	@ echo " \033[32m MiniRT build files cleaned\033[m"

fclean: clean
	@ rm -f $(NAME)
	@ echo " \033[32m MiniRT binary cleaned\033[m"

re: fclean $(LIBFT) all

.PHONY: clean fclean re all libft fclean_libft check_norm
