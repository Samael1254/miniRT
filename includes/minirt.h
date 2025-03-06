#ifndef MINIRT_FCTS_H
# define MINIRT_FCTS_H

# include <stdbool.h>

# include "minirt_defs.h"

// Init state //

// Initializes the program state
void		init_state(t_state *state, char *filename);
void		init_scene(t_state *state, char *filename);
int			retrieve_data(t_state *state, char **split);

// Parsing

// utils.c
t_vector3d	get_vector(char *line_vector, bool *error);
int			is_vector3d_in_range(t_vector3d vec, double min, double max);

// objects_list.c
void		add_object_to_list(t_state *state, char **split);

// object_sphere.c
t_object	*object_sphere(t_state *state, char **split);

// Events //

// Loops while waiting for events
void		loop_events(t_state *state);

// Check arguments //

// Checks if the program arguments are valid
int			check_arguments(int argc, char **argv);

// Errors //

// Prints an error
void		error(char const *type, char const *msg);
// Prints an error and exits the program
void		fatal_error(char const *type, char const *msg, t_state *state);

// Exit program //

// Frees the program state and exits the program
int			exit_program(t_state *state, int status);

// PRINT FOR DEBUGS
void		print_scene(t_scene scene);
void		print_ambiant_light(t_ambiant_light ambiant_light);
void		print_camera(t_camera camera);
void		print_point_light(t_point_light light);
void		print_scene(t_scene scene);
void		print_sphere(t_sphere sphere);

#endif
