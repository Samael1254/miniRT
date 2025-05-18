NAME = miniRT

SRCS_DIR = srcs/
BUILD_DIR = build/
HEADERS_DIR = includes/

HEADERS = minirt_defs.h minirt_base.h minirt_graphics.h minirt_light.h minirt_normals.h \
		  minirt_parsing.h minirt_bvh.h minirt_errors.h minirt_intersections.h minirt_mapping.h \
		  minirt_obj_parser.h minirt_raytracing.h

HEADERS := $(addprefix $(HEADERS_DIR), $(HEADERS))

SRCS_MAIN := main.c exit_program.c events.c init_state.c \
			  time.c events_utils.c events_utils_execution.c events_utils_toggle.c

SRCS_BVH := aabb_utils.c create_bvh.c bvh_free.c bvh_triangle.c print_aabb.c \
			 intersect_aabb.c

SRCS_PARSING := init_scene.c insert_in_struct.c utils.c utils2.c objects_list.c \
				object_sphere.c object_plane.c object_cylinder.c utils_general_objects.c \
				create_lights.c open_and_count_mats.c object_cone.c utils_mat.c object_mesh.c

SRCS_GRAPHICS := color.c graphics.c color_utils.c post_process.c post_process_utils.c post_process_utils2.c

SRCS_ERRORS := errors.c check_arguments.c

SRCS_RAYTRACING := raytracing.c intersections.c intersect_objects.c rays.c \
				   normals.c intersect_objects_utils.c intersect_bvh.c object_normal.c \
				   ray_utils.c intersect_objects_utils2.c

SRCS_LIGHT := light.c light_utils.c light_utils2.c recursive_light.c shade_from_one_light_utils.c

SRCS_TEXTURING := uv_mapping.c normal_map.c mapping_utils.c object_mapping.c

SRCS_MESH := init_mesh.c mesh_utils.c parse_obj_element.c parse_obj_file.c

SRCS := $(addprefix $(SRCS_DIR)base/, $(SRCS_MAIN)) \
           $(addprefix $(SRCS_DIR)bvh/, $(SRCS_BVH)) \
           $(addprefix $(SRCS_DIR)parsing/, $(SRCS_PARSING)) \
           $(addprefix $(SRCS_DIR)graphics/, $(SRCS_GRAPHICS)) \
           $(addprefix $(SRCS_DIR)errors/, $(SRCS_ERRORS)) \
           $(addprefix $(SRCS_DIR)raytracing/, $(SRCS_RAYTRACING)) \
           $(addprefix $(SRCS_DIR)light/, $(SRCS_LIGHT)) \
           $(addprefix $(SRCS_DIR)texturing/, $(SRCS_TEXTURING)) \
           $(addprefix $(SRCS_DIR)mesh_parsing/, $(SRCS_MESH)) \

OBJS := $(addprefix $(BUILD_DIR), $(notdir $(SRCS:.c=.o)))

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I./libs/libft/includes -I./libs/mlx -I./libs/obj_parser/include/ #-fsanitize=undefined -g

LIBFT = ./libs/libft/lib/libft.a

MLX = ./libs/mlx/libmlx.a

OBJ_PARSER = ./libs/obj_parser/lib/libobjParser.a

LIBFLAGS := -lft -Llibs/libft/lib -lmlx -Llibs/mlx -lobjParser -Llibs/obj_parser/lib -lX11 -lXext -lm

$(NAME): $(LIBFT) $(MLX) $(OBJ_PARSER) $(OBJS) $(HEADERS)
	@ echo " \033[33mCompiling miniRT\033[m"
	@ $(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFLAGS)
	@ echo " \033[1;32m MiniRT\033[0;1;32m binary compiled\033[m"

$(BUILD_DIR)%.o: $(SRCS_DIR)*/%.c
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
	@ cd libs/mlx && $(MAKE) -s
	@ echo " \033[34m MiniLibX compiled\033[m"

$(OBJ_PARSER):
	@ cd libs/obj_parser && $(MAKE) -s

clean_libs:
	@ echo " \033[33mCleaning Libft\033[m"
	@ cd libs/libft && $(MAKE) -s fclean
	@ tput cuu1 && tput el
	@ tput cuu1 && tput el
	@ echo " \033[34m Libft cleaned\033[m"
	@ echo " \033[33mCleaning MiniLibX\033[m"
	@ cd libs/mlx && $(MAKE) -s clean
	@ cd libs/obj_parser && $(MAKE) -s fclean

libs: clean_libs $(LIBFT) $(MLX) $(OBJ_PARSER)

all: $(NAME)

clean:
	@ echo " \033[33mCleaning\033[m"
	@ rm -f $(OBJS)
	@ rm -rf $(BUILD_DIR)
	@ echo " \033[32m MiniRT build files cleaned\033[m"

fclean: clean
	@ rm -f $(NAME)
	@ echo " \033[32m MiniRT binary cleaned\033[m"

re: fclean all

.PHONY: clean fclean re all libft fclean_libft clean_libs
