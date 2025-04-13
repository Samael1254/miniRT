#include "ft_strings.h"
#include "minirt_base_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_raytracing_bonus.h"
#include "mlx.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_state	state;
	char	*fps_str;

	check_arguments(argc, argv);
	init_state(&state, argv[1]);
	ray_tracing(&state);
	fps_str = get_fps_string(get_time_diff(get_time(&state), state.start_time));
	mlx_string_put(state.display, state.win, WIN_Y - 10 - 6
		* ft_strlen(fps_str), 20, 0xFFFFFF, fps_str);
	free(fps_str);
	printf("Frame render time: %ld ms\n", get_time_diff(get_time(&state),
			state.start_time));
	info(NULL, "done, press ESC to close, H for help");
	loop_events(&state);
	warning("unusal exit", "program should be closed with ESC or cross");
	exit_program(&state, EXIT_FAILURE);
}
