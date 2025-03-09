#ifndef MINIRT_FCTS_H
# define MINIRT_FCTS_H

# include "minirt_defs.h"
# include <stdbool.h>

// Init state //

// Initializes the program state
void		init_state(t_state *state, char *filename);
void		init_scene(t_state *state, char *filename);
int			insert_in_struct(t_state *state, char **split);

// Parsing

// utils.c
t_vector3d	get_vector(char *line_vector, bool *error);
t_color		get_color(char *line_color, bool *error);
int			is_vector3d_in_range(t_vector3d vec, double min, double max);
int			is_t_color_valid(t_color color, double min, double max);

// objects_list.c
void		add_object_to_list(t_state *state, char **split);

// object_sphere.c
t_object	*object_sphere(t_state *state, char **split);
t_object	*object_plane(t_state *state, char **split);
t_object	*object_cylinder(t_state *state, char **split);

// Events //

// Loops while waiting for events
void		loop_events(t_state *state);

// Transform //

void		transform_scene(t_scene *scene);

// Ray tracing //

void		ray_tracing(t_state *state);

// Rays //

void		init_rays(t_camera camera, t_ray **rays);
void		shoot_rays(t_ray **rays, t_state *state);

// Intersections //

t_ray		intersect_scene(t_ray ray, t_list *objects);

// Light //

void		light_scene(t_ray **rays, t_state *state);

// Graphics //

int			rgb_to_int(t_color color);
t_color		init_color(unsigned char r, unsigned char g, unsigned char b);
t_color		get_sky_color(t_ray ray);
t_color		average_colors(t_color color1, t_color color2);
t_color		apply_brightness(t_color color, double brightness);
void		render_scene(t_state *state, t_ray **rays);

// Check arguments //

// Checks if the program arguments are valid
void		check_arguments(int argc, char **argv);

// Errors //

void		warning(char const *type, char const *msg);
void		info(char const *type, char const *msg);
// Prints an error and exits the program
void		error(char const *type, char const *msg, t_state *state);

// Exit program //

// Frees the program state and exits the program
int			exit_program(t_state *state, int status);

// PRINT FOR DEBUGS
void		print_scene(t_scene scene);
void		print_vector3d(t_vector3d vec);

#endif
