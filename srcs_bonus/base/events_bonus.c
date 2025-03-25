#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include "mlx.h"
#include <stdlib.h>

static void	recreate_image(t_state *state)
{
	void	*tmp;

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
}

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

static void	move_camera(t_state *state, t_camera *camera, enum e_keycode key)
{
	t_vector3d	translator;
	t_vector3d	axis;
	short		sign;

	axis = ft_init_vector3d(0);
	sign = 1;
	if (key == W_KEY || key == S_KEY)
		axis = camera->dir;
	else if (key == A_KEY || key == D_KEY)
		axis = ft_cross_vectors3d(ft_set_vector3d(0, 1, 0), camera->dir);
	else if (key == Q_KEY || key == E_KEY)
		axis = ft_set_vector3d(0, 1, 0);
	if (key == S_KEY || key == D_KEY || key == E_KEY)
		sign = -1;
	translator = ft_scale_vector3d(sign * camera->move_step, axis);
	camera->pos = ft_add_vectors3d(camera->pos, translator);
	recreate_image(state);
}

static void	rotate_camera(t_state *state, t_camera *camera,
		enum e_keycode keycode)
{
	double	angle;
	double	m_rot[4][4];

	angle = ft_deg_to_rad(camera->rot_step);
	if (keycode == L_KEY || keycode == K_KEY)
		angle *= -1;
	if (keycode == J_KEY || keycode == L_KEY)
		ft_set_base_rotation_matrix4d(m_rot, angle, Y_AXIS);
	else if (keycode == I_KEY || keycode == K_KEY)
		ft_set_rotation_matrix4d(m_rot, angle, camera->x_axis);
	camera->dir = ft_4dto3d_vector(ft_matrix_vector_product4d(m_rot,
				ft_3dto4d_vector(camera->dir)));
	if (keycode == J_KEY || keycode == L_KEY)
		camera->x_axis = ft_4dto3d_vector(ft_matrix_vector_product4d(m_rot,
					ft_3dto4d_vector(camera->x_axis)));
	camera->y_axis = ft_4dto3d_vector(ft_matrix_vector_product4d(m_rot,
				ft_3dto4d_vector(camera->y_axis)));
	recreate_image(state);
}

static int	key_pressed(enum e_keycode key, t_state *state)
{
	if (key == ESC_KEY)
		exit_program(state, EXIT_SUCCESS);
	if (key == UP_ARROW_KEY)
		modify_step_size(state, '+');
	if (key == DOWN_ARROW_KEY)
		modify_step_size(state, '-');
	if (key == RIGHT_ARROW_KEY)
		modify_rot_step_size(state, '+');
	if (key == LEFT_ARROW_KEY)
		modify_rot_step_size(state, '-');
	if (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY
		|| key == Q_KEY || key == E_KEY)
		move_camera(state, &state->scene.camera, key);
	if (key == J_KEY || key == L_KEY || key == I_KEY || key == K_KEY)
		rotate_camera(state, &state->scene.camera, key);
	if (key == H_KEY)
		display_help(state);
	return (1);
}

void	loop_events(t_state *state)
{
	mlx_hook(state->win, ON_KEYPRESS, 1L << 0, &key_pressed, state);
	mlx_hook(state->win, ON_CLIENTMSG, 0L, &exit_program, state);
	mlx_loop(state->display);
}
