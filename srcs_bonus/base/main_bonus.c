#include "minirt_base_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_raytracing_bonus.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_state	state;

	check_arguments(argc, argv);
	init_state(&state, argv[1]);
	ray_tracing(&state);
	state.end_time = get_time(&state);
	printf("Frame render time: %ld ms\n", get_time_diff(state.end_time,
			state.start_time));
	info(NULL, "done, press ESC to close, H for help");
	loop_events(&state);
	warning("unusal exit", "program should be closed with ESC or cross");
	exit_program(&state, EXIT_FAILURE);
}
