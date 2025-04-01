#ifndef MINIRT_PARSING_BONUS_H
# define MINIRT_PARSING_BONUS_H

# include "minirt_defs_bonus.h"
# include <stdbool.h>

// create_light_bonus.c
void		add_lights_to_list(t_state *state, char **split);

// init_scene_bonus.c
void		init_scene(t_state *state, char *filename);

// insert_in_struct.c
void		add_light(t_state *state, char **split);
int			insert_in_struct(t_state *state, char **split);

// object_cone_bonus.c
t_object	*object_cone(t_state *state, char **split);

// object_cylinder_bonus.c
t_object	*object_cylinder(t_state *state, char **split);

// object_mesh_bonus.c
t_object	*object_mesh(t_state *state, char **split);

// object_plane_bonus.c
t_object	*object_plane(t_state *state, char **split);

// object_sphere_bonus.c
t_object	*object_sphere(t_state *state, char **split);

// objects_list_bonus.c
void		add_object_to_list(t_state *state, char **split);

// open_and_count_mats_bonus.c
int			open_and_count_mats(t_state *state, char *filename);

// utils2_bonus.c
void		check_line(t_state *state, char **split, int split_len);

// utils_bonus.c
t_color		get_color(char *line_color, bool *error);

// utils_general_objects_bonus.c
void		ambiant_light_checker(t_state *state, char **split);

// utils_mat.c
void		get_normal_map_img(t_state *state, char *filename, t_material *mat);
void		get_texture_map_img(t_state *state, char *filename, t_material *mat);

#endif // !MINIRT_PARSING_BONUS_H
