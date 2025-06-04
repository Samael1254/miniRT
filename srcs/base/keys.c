#include "minirt_base.h"
#include "minirt_cli.h"
#include "minirt_defs.h"
#include "minirt_events.h"
#include "minirt_graphics.h"
#include <stdlib.h>

static void	render_keys(enum e_keycode key, t_state *state)
{
	if (key == L_KEY)
		toggle_lights(state);
	else if (key == K_KEY)
		toggle_aa(state);
	else if (key == P_KEY)
		change_post_processing(state);
}

static void	ui_keys(enum e_keycode key, t_state *state)
{
	if (key == F_KEY)
		toggle_fps(state);
	else if (key == H_KEY)
		toggle_help(state);
}

static void	modifier_keys(enum e_keycode key, t_keys_state *keys_state)
{
	if (key == ALT_KEY && !keys_state->hold_alt)
		keys_state->hold_alt = true;
	else if (key == MAJ_KEY && !keys_state->hold_shift)
		keys_state->hold_shift = true;
}

static void	movement_keys(enum e_keycode key, const t_keys_state *keys_state,
		t_state *state)
{
	if (!keys_state->hold_alt && (key == W_KEY || key == S_KEY || key == A_KEY
			|| key == D_KEY))
		move_camera(state, &state->scene.camera, key);
	else if (keys_state->hold_alt && (key == W_KEY || key == S_KEY
			|| key == A_KEY || key == D_KEY))
		rotate_camera(state, &state->scene.camera, key);
	else if (key == UP_ARROW_KEY)
		modify_step_size(state, '+');
	else if (key == DOWN_ARROW_KEY)
		modify_step_size(state, '-');
	else if (key == LEFT_ARROW_KEY)
		modify_rot_step_size(state, '-');
	else if (key == RIGHT_ARROW_KEY)
		modify_rot_step_size(state, '+');
}

static void	program_keys(enum e_keycode key, t_state *state)
{
	if (key == ESC_KEY)
		exit_program(state, EXIT_SUCCESS);
	else if (key == SPACE_KEY)
		save_image(state);
	else if (key == TAB_KEY)
		toggle_command_mode(state);
}

int	key_pressed(enum e_keycode key, t_state *state)
{
	t_keys_state	*keys_state;

	keys_state = &state->keys_state;
	modifier_keys(key, keys_state);
	movement_keys(key, keys_state, state);
	render_keys(key, state);
	ui_keys(key, state);
	program_keys(key, state);
	return (0);
}

int	key_released(int key, t_state *state)
{
	if (key == ALT_KEY && state->keys_state.hold_alt)
		state->keys_state.hold_alt = false;
	if (key == MAJ_KEY && state->keys_state.hold_shift)
		state->keys_state.hold_shift = false;
	return (0);
}
