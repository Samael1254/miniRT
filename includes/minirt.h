#ifndef MINIRT_FCTS_H
# define MINIRT_FCTS_H

# include "minirt_defs.h"
# include <stdbool.h>

// Init state //

// Initializes the program state
void			init_state(t_state *state, char *filename);
void			init_scene(t_state *state, char *filename);
int				insert_in_struct(t_state *state, char **split);

// Parsing

// utils.c
t_vector3d		get_vector(char *line_vector, bool *error);
t_color			get_color(char *line_color, bool *error);
bool			is_vector3d_in_range(t_vector3d vec, double min, double max);
bool			is_t_color_valid(t_color color, double min, double max);
bool			is_norm_vector_valid(t_vector3d vec);

// utils2.c
bool			ft_check_error_line(char **split, int len);
bool			ft_check_split_data(char **split);
void			check_line(t_state *state, char **split, int split_len);

// utils_general_objects.c
void			ambiant_light_checker(t_state *state, char **split);

// objects_list.c
void			add_object_to_list(t_state *state, char **split);

// object_sphere.c
t_object		*object_sphere(t_state *state, char **split);
t_object		*object_plane(t_state *state, char **split);
t_object		*object_cylinder(t_state *state, char **split);

// Events //

// Loops while waiting for events
void			loop_events(t_state *state);

// Transform //

void			transform_scene(t_scene *scene);

// Ray tracing //

void			ray_tracing(t_state *state);

// Intersections //

t_intersection	intersect_scene(t_ray ray, t_list *objects);

// Graphics //

int				rgb_to_int(t_color color);
void			put_pixel(t_img_data *img, t_ivector2d coords, t_color color);
t_color			get_sky_color(t_ray ray);

// Check arguments //

// Checks if the program arguments are valid
int				check_arguments(int argc, char **argv);

// Errors //

void			warning(char const *type, char const *msg);
void			info(char const *type, char const *msg);
// Prints an error and exits the program
void			error(char const *type, char const *msg, t_state *state);

// Exit program //

// Frees the program state and exits the program
int				exit_program(t_state *state, int status);

// PRINT FOR DEBUGS
void			print_scene(t_scene scene);
void			print_ambiant_light(t_ambiant_light ambiant_light);
void			print_camera(t_camera camera);
void			print_point_light(t_point_light light);
void			print_scene(t_scene scene);
void			print_sphere(t_sphere sphere);

#endif
