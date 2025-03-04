#include "ft_strings.h"
#include <unistd.h>

void	error(char const *fname, char const *msg)
{
	write(2, "error: ", 7);
	if (fname)
	{
		write(2, fname, ft_strlen(fname));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
