#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_state	state;

	check_arguments(argc, argv);
	init_state(&state, argv[1]);
	ray_tracing(&state);
	info(NULL, "done, press ESC to close");
	printf("Warnings raised: %u\n", warnings_number(false));
	loop_events(&state);
	warning("unusal exit", "program should be closed with ESC or cross");
	exit_program(&state, EXIT_FAILURE);
}
