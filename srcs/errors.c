#include "ft_strings.h"
#include "minirt.h"
#include <stdlib.h>
#include <unistd.h>

void	error(char const *type, char const *msg)
{
	write(2, "error: ", 7);
	if (type)
	{
		write(2, type, ft_strlen(type));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	fatal_error(char const *type, char const *msg, t_state *state)
{
	error(type, msg);
	exit_program(state, EXIT_FAILURE);
}
