#include "ft_strings.h"
#include "minirt_base.h"
#include "minirt_cli.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_events.h"
#include "minirt_raytracing.h"
#include <bits/types/struct_timeval.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <readline/rltypedefs.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_state	state;
	char	*scene_name;

	check_arguments(argc, argv);
	if (argc > 1)
		scene_name = ft_strdup(argv[1]);
	else
		scene_name = select_scene();
	init_state(&state, scene_name);
	init_cli(&state.cli);
	ray_tracing(&state);
	loop_events(&state);
	warning("unusal exit", "program should be closed with ESC or cross");
	exit_program(&state, EXIT_FAILURE);
}
