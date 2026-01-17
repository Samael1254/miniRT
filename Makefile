NAME = miniRT

SRCS_DIR = srcs/
BUILD_DIR = build/
HEADERS_DIR = includes/

HEADERS = minirt_defs.h minirt_base.h minirt_graphics.h minirt_light.h minirt_normals.h \
		  minirt_parsing.h minirt_bvh.h minirt_errors.h minirt_intersections.h minirt_mapping.h \
		  minirt_obj_parser.h minirt_raytracing.h

HEADERS := $(addprefix $(HEADERS_DIR), $(HEADERS))

SRCS_MAIN := main.c exit_program.c events.c init_state.c \
			 time.c camera_movement.c events_toggle.c \
			 select_scene.c interaction.c reload_image.c keys.c

SRCS_BVH := aabb_utils.c create_bvh.c bvh_free.c bvh_triangle.c print_aabb.c \
			 intersect_aabb.c

SRCS_PARSING := init_scene.c insert_in_struct.c utils.c utils2.c objects_list.c \
				object_sphere.c object_plane.c object_cylinder.c utils_general_objects.c \
				create_lights.c open_and_count_mats.c object_cone.c utils_mat.c object_mesh.c

SRCS_GRAPHICS := color.c graphics.c color_utils.c post_process.c post_process_utils.c post_process_filters.c \
				 save_image.c

SRCS_ERRORS := errors.c check_arguments.c

SRCS_RAYTRACING := raytracing.c intersections.c intersect_objects.c rays.c \
				   normals.c intersect_objects_utils.c intersect_bvh.c object_normal.c \
				   ray_utils.c intersect_objects_utils2.c

SRCS_LIGHT := light.c light_utils.c light_utils2.c recursive_light.c shade_from_one_light_utils.c

SRCS_TEXTURING := uv_mapping.c normal_map.c mapping_utils.c object_mapping.c

SRCS_MESH := init_mesh.c mesh_utils.c parse_obj_element.c parse_obj_file.c

SRCS_CLI := cli.c commands.c commands_utils.c

SRCS := $(addprefix $(SRCS_DIR)base/, $(SRCS_MAIN)) \
           $(addprefix $(SRCS_DIR)bvh/, $(SRCS_BVH)) \
           $(addprefix $(SRCS_DIR)parsing/, $(SRCS_PARSING)) \
           $(addprefix $(SRCS_DIR)graphics/, $(SRCS_GRAPHICS)) \
           $(addprefix $(SRCS_DIR)errors/, $(SRCS_ERRORS)) \
           $(addprefix $(SRCS_DIR)raytracing/, $(SRCS_RAYTRACING)) \
           $(addprefix $(SRCS_DIR)light/, $(SRCS_LIGHT)) \
           $(addprefix $(SRCS_DIR)texturing/, $(SRCS_TEXTURING)) \
           $(addprefix $(SRCS_DIR)mesh_parsing/, $(SRCS_MESH)) \
           $(addprefix $(SRCS_DIR)cli/, $(SRCS_CLI)) \

OBJS := $(addprefix $(BUILD_DIR), $(notdir $(SRCS:.c=.o)))

DEPS = $(OBJS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I./includes/libft -I./includes/mlx -MMD -MP -O3 -Wno-error=unused-result -Wno-unused-result

LIBFT = ./libs/libft.a

MLX = ./libs/libmlx.a

LDFLAGS := -lft -Llibs -lmlx -Llibs -lX11 -lXext -lm -lreadline -pthread

$(NAME): $(OBJS) $(HEADERS)
	@ echo " \033[33mCompiling miniRT\033[m"
	@ $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	@ echo " \033[1;32m MiniRT\033[0;1;32m binary compiled\033[m"

$(BUILD_DIR)%.o: $(SRCS_DIR)*/%.c
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@ echo " \033[33mCleaning\033[m"
	@ rm -f $(OBJS) $(DEPS)
	@ rm -rf $(BUILD_DIR)
	@ echo " \033[32m MiniRT build files cleaned\033[m"

fclean: clean
	@ rm -f $(NAME)
	@ echo " \033[32m MiniRT binary cleaned\033[m"

re: fclean all

.PHONY: clean fclean re all

-include $(DEP)
