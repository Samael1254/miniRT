#include "ft_strings.h"
#include "minirt.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int	warnings_number(bool add)
{
	static int	n_errors;

	if (add)
		n_errors++;
	return (n_errors);
}

void	warning(char const *type, char const *msg)
{
	write(2, "\e[33;1mWarning: \e[0m", 20);
	if (type)
	{
		write(2, "\e[1m", 4);
		write(2, type, ft_strlen(type));
		write(2, ": \e[0m", 6);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	warnings_number(true);
}

void	info(char const *type, char const *msg)
{
	write(2, "\e[34;1mInfo: \e[0m", 17);
	if (type)
	{
		write(2, "\e[1m", 4);
		write(2, type, ft_strlen(type));
		write(2, ": \e[0m", 6);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	error(char const *type, char const *msg, t_state *state)
{
	write(2, "\e[31;1mError: \e[0m", 18);
	if (type)
	{
		write(2, "\e[1m", 4);
		write(2, type, ft_strlen(type));
		write(2, ": \e[0m", 6);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit_program(state, EXIT_FAILURE);
}
