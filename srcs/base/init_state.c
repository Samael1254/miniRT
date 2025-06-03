/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/06/03 20:03:13 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"
#include "minirt_cli.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_parsing.h"
#include "mlx.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>

static void	init_mlx(t_state *state)
{
	state->display = mlx_init();
	if (!state->display)
		error("init_mlx", "failed to create display", state);
	state->win = mlx_new_window(state->display, WIN_X, WIN_Y, "miniRT");
	if (!state->win)
		error("init_mlx", "failed to create window", state);
	state->processed_img.img = NULL;
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
	state->display = NULL;
	state->redraw_column = 0;
	state->rendering = false;
	state->scene.lights = NULL;
	state->scene.objects = NULL;
	for (int i = 0; i < ID_LIST_SIZE; i++)
		state->id_list[i] = NULL;
	state->len_mats_tab = 0;
	state->mats_tab = NULL;
	state->keys_state.hold_alt = 0;
	state->keys_state.hold_shift = 0;
	state->keys_state.toggle_lights = false;
	state->keys_state.toggle_fps = false;
	state->keys_state.toggle_help = false;
	state->keys_state.toggle_aa = false;
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
