/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_toggle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"

void	toggle_lights(t_state *state)
{
	if (state->toggle_lights)
		state->toggle_lights = false;
	else
		state->toggle_lights = true;
	recreate_image(state);
}

void	toggle_aa(t_state *state)
{
	if (state->toggle_aa)
		state->toggle_aa = false;
	else
		state->toggle_aa = true;
	recreate_image(state);
}

void	toggle_help(t_state *state)
{
	if (state->toggle_help)
		state->toggle_help = false;
	else
		state->toggle_help = true;
	reload_image(state);
}

void	toggle_fps(t_state *state)
{
	if (state->toggle_fps)
		state->toggle_fps = false;
	else
		state->toggle_fps = true;
	reload_image(state);
}

void	change_post_processing(t_state *state)
{
	state->post_process = (state->post_process + 1) % 9;
	recreate_image(state);
}
