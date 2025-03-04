#ifndef MINIRT_H
# define MINIRT_H

// MACROS

# define FALSE 0
# define TRUE 1

// ENUMS

// Event codes
enum	e_event
{
	ON_KEYPRESS = 2,
	ON_CLIENTMSG = 33,
};

// Keyboard codes
enum	e_keycode
{
	K_ESC = 0xff1b,
};

// FUNCTIONS

// Check arguments

// Checks if the program arguments are valid
int		check_arguments(int argc, char **argv);

// Errors

// Prints an error
void	error(char const *fname, char const *msg);

#endif
