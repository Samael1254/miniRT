#include "ft_algebra.h"
#include "minirt_base_bonus.h"
#include "minirt_defs_bonus.h"
#include "mlx.h"
#include <stdlib.h>

static int	display_help(t_state *state)
{
	mlx_string_put(state->display, state->win, 20, 20, 0xFFFFFF, "-- HELP --");
	mlx_string_put(state->display, state->win, 20, 40, 0xFFFFFF,
		"Move: WASDQE");
	mlx_string_put(state->display, state->win, 20, 55, 0xFFFFFF,
		"Rotate: JLIK");
	mlx_string_put(state->display, state->win, 20, 70, 0xFFFFFF,
		"Change movement speed: UP/DOWN");
	mlx_string_put(state->display, state->win, 20, 85, 0xFFFFFF,
		"Change rotation speed: LEFT/RIGHT");
	mlx_string_put(state->display, state->win, 20, 100, 0xFFFFFF,
		"Exit program: ESC");
	return (0);
}

void	move_camera(t_state *state, t_camera *camera, enum e_keycode key)
{
	t_vec3	translator;
	t_vec3	axis;
	short	sign;

	axis = ft_init_vec3(0);
	sign = 1;
	if (key == SCROLL_UP || key == SCROLL_DOWN)
		axis = camera->dir;
	else if (key == A_KEY || key == D_KEY)
		axis = ft_cross_vec3(ft_set_vec3(0, 1, 0), camera->dir);
	else if (key == W_KEY || key == S_KEY)
		axis = camera->y_axis;
	if (key == SCROLL_DOWN || key == D_KEY || key == S_KEY)
		sign = -1;
	translator = ft_scale_vec3(sign * camera->move_step, axis);
	camera->pos = ft_add_vec3(camera->pos, translator);
	recreate_image(state);
}

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
	if (key == LEFT_ARROW_KEY)
		modify_rot_step_size(state, '-');
	if (key == H_KEY)
		display_help(state);
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
