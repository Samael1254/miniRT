#ifndef MINIRT_FCTS_H
# define MINIRT_FCTS_H

# include "minirt_defs.h"

// Init state //

// Initializes the program state
void	init_state(t_state *state, char *filename);
void	init_scene(t_state *state, char *filename);

// Events //

// Loops while waiting for events
void	loop_events(t_state *state);

// Check arguments //

// Checks if the program arguments are valid
int		check_arguments(int argc, char **argv);

// Errors //

// Prints an error
void	error(char const *type, char const *msg);
// Prints an error and exits the program
void	fatal_error(char const *type, char const *msg, t_state *state);

// Exit program //

// Frees the program state and exits the program
int		exit_program(t_state *state, int status);

#endif
