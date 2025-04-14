/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "minirt_base_bonus.h"
#include "minirt_defs_bonus.h"
#include "mlx.h"
#include <stdlib.h>

static void	rotate_camera(t_state *state, t_camera *camera,
		enum e_keycode keycode)
{
	double	angle;
	double	m_rot[4][4];

	angle = ft_deg_to_rad(camera->rot_step);
	if (keycode == D_KEY || keycode == S_KEY)
		angle *= -1;
	if (keycode == A_KEY || keycode == D_KEY)
		ft_set_base_rotation_mat4(m_rot, angle, Y_AXIS);
	else if (keycode == W_KEY || keycode == S_KEY)
		ft_set_rotation_mat4(m_rot, angle, camera->x_axis);
	camera->dir = ft_4dto3d_vector(ft_mat_vec_product4(m_rot,
				ft_3dto4d_vector(camera->dir)));
	if (keycode == A_KEY || keycode == D_KEY)
		camera->x_axis = ft_4dto3d_vector(ft_mat_vec_product4(m_rot,
					ft_3dto4d_vector(camera->x_axis)));
	camera->y_axis = ft_4dto3d_vector(ft_mat_vec_product4(m_rot,
				ft_3dto4d_vector(camera->y_axis)));
	recreate_image(state);
}

static void	key_pressed_utils(enum e_keycode key, t_state *state)
{
	if (key == LEFT_ARROW_KEY)
		modify_rot_step_size(state, '-');
	if (key == L_KEY)
		toggle_lights(state);
	if (key == F_KEY)
		toggle_fps(state);
	if (key == H_KEY)
		toggle_help(state);
	if (key == K_KEY)
		toggle_aa(state);
	if (key == P_KEY)
		change_post_processing(state);
}

static int	key_pressed(enum e_keycode key, t_state *state)
{
	if (key == ESC_KEY)
		exit_program(state, EXIT_SUCCESS);
	if (key == ALT_KEY && state->hold_alt == 0)
		state->hold_alt = 1;
	if (state->hold_alt == 0 && (key == W_KEY || key == S_KEY || key == A_KEY
			|| key == D_KEY))
		move_camera(state, &state->scene.camera, key);
	else if (state->hold_alt == 1 && (key == W_KEY || key == S_KEY
			|| key == A_KEY || key == D_KEY))
		rotate_camera(state, &state->scene.camera, key);
	if (key == UP_ARROW_KEY)
		modify_step_size(state, '+');
	if (key == DOWN_ARROW_KEY)
		modify_step_size(state, '-');
	if (key == RIGHT_ARROW_KEY)
		modify_rot_step_size(state, '+');
	key_pressed_utils(key, state);
	return (1);
}

void	loop_events(t_state *state)
{
	mlx_hook(state->win, 2, 1L << 0, key_pressed, state);
	mlx_hook(state->win, 3, 1L << 1, end_hold_alt_hook, state);
	mlx_hook(state->win, 4, 1L << 2, on_mouse_moov, state);
	mlx_hook(state->win, ON_CLIENTMSG, 0L, exit_program, state);
	mlx_loop(state->display);
}
