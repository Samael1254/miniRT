#ifndef MINIRT_H
# define MINIRT_H

/* MACROS */

# define FALSE 0
# define TRUE 1

# define WIN_X 1600
# define WIN_Y 1000

/* ENUMS */

// Event codes
enum		e_event
{
	ON_KEYPRESS = 2,
	ON_CLIENTMSG = 33,
};

// Keyboard codes
enum		e_keycode
{
	K_ESC = 0xff1b,
};

/* STRUCTS */

typedef struct s_state
{
	void	*display;
	void	*win;
	void	*img;
}			t_state;

/* FUNCTIONS */

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
void		exit_program(t_state *state, int status);

#endif
