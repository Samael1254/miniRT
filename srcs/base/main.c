#include "minirt.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_state	state;

	check_arguments(argc, argv);
	init_state(&state, argv[1]);
	ray_tracing(&state);
	loop_events(&state);
	exit_program(&state, EXIT_SUCCESS);
}
