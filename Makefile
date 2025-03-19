NAME = miniRT

SOURCES_DIR = srcs/
BONUS_DIR = srcs_bonus/
BUILD_DIR = build/
HEADERS_DIR = includes/
BONUS_HEADERS_DIR = includes_bonus/

HEADERS = minirt.h minirt_defs.h
HEADERS := $(addprefix $(HEADERS_DIR), $(HEADERS))

BONUS_HEADERS = minirt_bonus.h minirt_defs_bonus.h
BONUS_HEADERS := $(addprefix $(BONUS_HEADERS_DIR), $(BONUS_HEADERS))

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


BONUS_MAIN := main_bonus.c exit_program_bonus.c events_bonus.c init_state_bonus.c

BONUS_PARSING := init_scene_bonus.c insert_in_struct_bonus.c utils_bonus.c utils2_bonus.c objects_list_bonus.c \
				object_sphere_bonus.c object_plane_bonus.c object_cylinder_bonus.c utils_general_objects_bonus.c \
				create_lights_bonus.c open_and_count_mats_bonus.c object_cone_bonus.c

BONUS_GRAPHICS := color_bonus.c graphics_bonus.c

BONUS_ERRORS := errors_bonus.c check_arguments_bonus.c

BONUS_RAYTRACING := raytracing_bonus.c intersections_bonus.c intersect_objects_bonus.c rays_bonus.c \
				   normals_bonus.c

BONUS_LIGHT := light_bonus.c phong_bonus.c

BONUS_TEXTURING := uv_mapping_bonus.c

BONUS := $(addprefix $(BONUS_DIR)base/, $(BONUS_MAIN)) \
           $(addprefix $(BONUS_DIR)parsing/, $(BONUS_PARSING)) \
           $(addprefix $(BONUS_DIR)graphics/, $(BONUS_GRAPHICS)) \
           $(addprefix $(BONUS_DIR)errors/, $(BONUS_ERRORS)) \
           $(addprefix $(BONUS_DIR)raytracing/, $(BONUS_RAYTRACING)) \
           $(addprefix $(BONUS_DIR)light/, $(BONUS_LIGHT)) \
           $(addprefix $(BONUS_DIR)texturing/, $(BONUS_TEXTURING)) \


MANDATORY_OBJS := $(addprefix $(BUILD_DIR)mandatory/, $(notdir $(SOURCES:.c=.o)))

BONUS_OBJS := $(addprefix $(BUILD_DIR)bonus/, $(notdir $(BONUS:.c=.o)))

MODE ?= mandatory

ifeq ($(MODE), mandatory)
	OBJS = $(MANDATORY_OBJS)
else ifeq ($(MODE), bonus)
	OBJS = $(BONUS_OBJS)
else
	$(error Invalid MODE. Use 'mandatory' or 'bonus'.)
endif

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I./includes_bonus -I./libs/libft/includes -I./libs/mlx #-g

LIBFT = ./libs/libft/lib/libft.a

MLX = ./libs/mlx/libmlx.a

LIBFLAGS := -lft -Llibs/libft/lib -lmlx -Llibs/mlx -lX11 -lXext -lm

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(HEADERS)
	@ echo " \033[33mCompiling miniRT $(MODE)\033[m"
	@ if [ "$(MODE)" = "mandatory" ]; then \
		rm -f $(BONUS_OBJS); \
		rm -rf $(BUILD_DIR)bonus; \
	fi
	@ $(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFLAGS)
	@ echo " \033[1;32m MiniRT \033[4m$(MODE)\033[0;1;32m binary compiled\033[m"

bonus: $(LIBFT) $(MLX) $(BONUS_OBJS) $(BONUS_HEADERS)
	@ rm -f $(MANDATORY_OBJS)
	@ rm -rf $(BUILD_DIR)mandatory
	@if ! $(MAKE) -s -n MODE=bonus | grep -q .; then \
		echo "make: 'miniRT' (bonus) is up to date."; \
	fi
	@ $(MAKE) -s MODE=bonus

$(BUILD_DIR)mandatory/%.o: $(SOURCES_DIR)*/%.c
	@ mkdir -p $(BUILD_DIR)mandatory
	@ $(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)bonus/%.o: $(BONUS_DIR)*/%.c
	@ mkdir -p $(BUILD_DIR)bonus
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

all: $(NAME)

clean:
	@ echo " \033[33mCleaning\033[m"
	@ rm -f $(BONUS_OBJS) $(MANDATORY_OBJS)
	@ rm -rf $(BUILD_DIR)mandatory
	@ rm -rf $(BUILD_DIR)bonus
	@ rm -rf $(BUILD_DIR)
	@ echo " \033[32m MiniRT build files cleaned\033[m"

fclean: clean
	@ rm -f $(NAME)
	@ echo " \033[32m MiniRT binary cleaned\033[m"

re: fclean $(LIBFT) all

.PHONY: clean fclean re all libft fclean_libft check_norm bonus
