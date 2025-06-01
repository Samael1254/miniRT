/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_toggle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/06/01 21:10:50 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"
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
