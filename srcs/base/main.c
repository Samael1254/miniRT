#include "minirt.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_state	state;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	init_state(&state, argv[1]);
	loop_events(&state);
	exit_program(&state, EXIT_SUCCESS);
}
