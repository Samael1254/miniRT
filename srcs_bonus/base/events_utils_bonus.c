/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "minirt_base_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_raytracing_bonus.h"
#include "mlx.h"
#include <bits/types/struct_timeval.h>
#include <stdlib.h>
#include <unistd.h>

void	display_fps(t_state *state)
{
	char	*fps_str;

	if (!state->toggle_fps)
		return ;
	fps_str = get_fps_string(get_time_diff(state->end_time, state->start_time));
	if (!fps_str)
		error("malloc failed", "in get_fps_string", state);
	mlx_string_put(state->display, state->win, WIN_X - 10 - 6
		* ft_strlen(fps_str), 20, 0xFFFFFF, fps_str);
	free(fps_str);
}

void	reload_image(t_state *state)
{
	mlx_clear_window(state->display, state->win);
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
	display_fps(state);
	display_help(state);
}

void	recreate_image(t_state *state)
{
	void	*tmp;

	info(NULL, "LOADING...");
	state->start_time = get_time(state);
	tmp = state->img_data.img;
	state->img_data.img = mlx_new_image(state->display, WIN_X, WIN_Y);
	if (!state->img_data.img)
		error("init_mlx", "failed to create img", state);
	state->img_data.addr = mlx_get_data_addr(state->img_data.img,
			&state->img_data.bp_pixel, &state->img_data.line_len,
			&state->img_data.endian);
	if (!state->img_data.addr)
		error("init_mlx", "failed to retrieve addr", state);
	shoot_rays(state);
	mlx_destroy_image(state->display, tmp);
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
	write(1, "\e[1A\e[2K", 8);
	state->end_time = get_time(state);
	display_fps(state);
	display_help(state);
}

int	on_mouse_moov(enum e_keycode key, int x, int y, t_state *state)
{
	(void)x;
	(void)y;
	if (key == SCROLL_UP)
		move_camera(state, &state->scene.camera, SCROLL_UP);
	if (key == SCROLL_DOWN)
		move_camera(state, &state->scene.camera, SCROLL_DOWN);
	return (0);
}

int	end_hold_alt_hook(int button, t_state *state)
{
	if (button == ALT_KEY && state->hold_alt == 1)
		state->hold_alt = 0;
	return (0);
}
