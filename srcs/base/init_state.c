/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_parsing.h"
#include "mlx.h"
#include <stddef.h>

static void	init_mlx(t_state *state)
{
	state->display = mlx_init();
	if (!state->display)
		error("init_mlx", "failed to create display", state);
	state->win = mlx_new_window(state->display, WIN_X, WIN_Y, "miniRT");
	if (!state->win)
		error("init_mlx", "failed to create window", state);
	state->img_data.img = mlx_new_image(state->display, WIN_X, WIN_Y);
	if (!state->img_data.img)
		error("init_mlx", "failed to create img", state);
	state->img_data.addr = mlx_get_data_addr(state->img_data.img,
			&state->img_data.bp_pixel, &state->img_data.line_len,
			&state->img_data.endian);
	if (!state->img_data.addr)
		error("init_mlx", "failed to retrieve addr", state);
}

static void	initialize_state(t_state *state)
{
	int	i;

	i = 0;
	state->display = NULL;
	state->scene.lights = NULL;
	state->scene.objects = NULL;
	while (i < ID_LIST_SIZE)
		state->id_list[i++] = NULL;
	state->len_mats_tab = 0;
	state->mats_tab = NULL;
	state->hold_alt = 0;
	state->toggle_lights = false;
	state->toggle_fps = false;
	state->toggle_help = false;
	state->toggle_aa = false;
	state->post_process = PP_NONE;
}

void	init_state(t_state *state, char *filename)
{
	info("Starting minirt bonus version with following scene", filename);
	info(NULL, "initialization...");
	initialize_state(state);
	init_mlx(state);
	init_scene(state, filename);
	state->start_time = get_time(state);
}
