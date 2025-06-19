#include "minirt_base.h"
#include "ft_strings.h"
#include "minirt_base.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include "mlx.h"
#include <bits/types/struct_timeval.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"
#include "minirt_defs.h"
#include "minirt_graphics.h"

void	toggle_lights(t_state *state)
{
	if (state->keys_state.toggle_lights)
		state->keys_state.toggle_lights = false;
	else
		state->keys_state.toggle_lights = true;
	recreate_image(state);
}

void	toggle_aa(t_state *state)
{
	if (state->keys_state.toggle_aa)
		state->keys_state.toggle_aa = false;
	else
		state->keys_state.toggle_aa = true;
	recreate_image(state);
}

void	toggle_help(t_state *state)
{
	if (state->keys_state.toggle_help)
		state->keys_state.toggle_help = false;
	else
		state->keys_state.toggle_help = true;
	reload_image(state);
}

void	toggle_fps(t_state *state)
{
	if (state->keys_state.toggle_fps)
		state->keys_state.toggle_fps = false;
	else
		state->keys_state.toggle_fps = true;
	reload_image(state);
}

void	toggle_command_mode(t_state *state)
{
	if (state->rendering)
		return;
	state->keys_state.toggle_command = true;
	state->post_process = PP_DARK;
	post_process(state);
	reload_image(state);
}

void	change_post_processing(t_state *state)
{
	if (!state->keys_state.hold_shift)
		state->post_process = (state->post_process + 1) % NB_FILTERS;
	else
		state->post_process = (state->post_process - 1 + NB_FILTERS)
			% NB_FILTERS;
	if (state->post_process != PP_NONE)
		post_process(state);
	reload_image(state);
}

void	display_help(t_state *state)
{
	if (!state->keys_state.toggle_help)
		return ;
	mlx_string_put(state->display, state->win, 20, 20, 0xFFFFFF, "-- HELP --");
	mlx_string_put(state->display, state->win, 20, 40, 0xFFFFFF,
		"Move: WASD");
	mlx_string_put(state->display, state->win, 20, 55, 0xFFFFFF,
		"Zoom: Mouse wheel");
	mlx_string_put(state->display, state->win, 20, 70, 0xFFFFFF,
		"Rotate: ALT + WASD");
	mlx_string_put(state->display, state->win, 20, 85, 0xFFFFFF,
		"Change movement speed: UP/DOWN");
	mlx_string_put(state->display, state->win, 20, 100, 0xFFFFFF,
		"Change rotation speed: LEFT/RIGHT");
	mlx_string_put(state->display, state->win, 20, 115, 0xFFFFFF,
		"Show source light(s): L");
	mlx_string_put(state->display, state->win, 20, 130, 0xFFFFFF,
		"Change post-process: P (Shift-P to go backwards)");
	mlx_string_put(state->display, state->win, 20, 145, 0xFFFFFF,
		"Anti-aliasing: K");
	mlx_string_put(state->display, state->win, 20, 160, 0xFFFFFF,
		"Show FPS: F");
	mlx_string_put(state->display, state->win, 20, 175, 0xFFFFFF,
		"Save image: SPACE");
	mlx_string_put(state->display, state->win, 20, 190, 0xFFFFFF,
		"Exit program: ESC");
}

void	display_fps(t_state *state)
{
	char	*fps_str;

	if (!state->keys_state.toggle_fps)
		return ;
	fps_str = get_fps_string(get_time_diff(state->end_time, state->start_time));
	if (!fps_str)
		error("malloc failed", "in get_fps_string", state);
	mlx_string_put(state->display, state->win, WIN_X - 10 - 6
		* ft_strlen(fps_str), 20, 0xFFFFFF, fps_str);
	free(fps_str);
}
