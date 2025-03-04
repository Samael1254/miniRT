#include "minirt.h"
#include "stddef.h"

int	check_arguments(int argc, char **argv)
{
	if (argc == 1)
	{
		error(NULL, "no .rt scene file provided");
		return (TRUE);
	}
	if (argc > 2)
	{
		error(NULL, "too many arguments (only one accepted)");
		return (TRUE);
	}
	(void)argv;
	return (FALSE);
}
