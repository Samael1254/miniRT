#include "minirt_base.h"
#include "minirt_cli.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include "minirt_raytracing.h"
#include <pthread.h>
// clang-format off
#include <stdio.h>
#include <readline/readline.h>
// clang-format on
#include <stdlib.h>

static void evaluate_cli(t_state *state)
{
	pthread_mutex_lock(&state->cli.mutex);
	if (state->cli.is_closed)
	{
		pthread_mutex_unlock(&state->cli.mutex);
		exit_program(state, EXIT_SUCCESS);
	}
	if (state->cli.is_new_command)
	{
		pthread_mutex_unlock(&state->cli.mutex);
		process_command(state);
	}
	else
		pthread_mutex_unlock(&state->cli.mutex);
}

int render_loop(t_state *state)
{
	evaluate_cli(state);
	if (!state->rendering)
		return (0);
	if (state->redraw_column >= PARTIAL_RENDER)
	{
		state->rendering = false;
		return (0);
	}
	state->start_time = get_time(state);
	shoot_rays(state, state->redraw_column);
	state->end_time = get_time(state);
	if (state->post_process != PP_NONE)
		post_process(state);
	reload_image(state);
	state->redraw_column++;
	return (0);
}

void ray_tracing(t_state *state)
{
	info(NULL, "Ray-tracing...");
	state->redraw_column = 0;
	state->rendering = true;
	info(NULL, "press ESC to close, H for help");
	state->end_time = get_time(state);
}
