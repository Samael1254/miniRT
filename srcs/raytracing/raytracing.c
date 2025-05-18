/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 19:23:49 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include "minirt_raytracing.h"
#include <stdlib.h>

int	render_loop(t_state *state)
{
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

void	ray_tracing(t_state *state)
{
	info(NULL, "ray tracing...");
	state->redraw_column = 0;
	state->rendering = true;
	info(NULL, "done, press ESC to close, H for help");
	state->end_time = get_time(state);
}
