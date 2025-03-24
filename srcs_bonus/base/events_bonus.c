#include "ft_algebra.h"
#include "minirt_bonus.h"
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

static void	move_camera(t_state *state, t_camera *camera, char sign)
{
	if (sign == '+')
	{
		camera->pos.x += camera->dir.x * camera->deplacement_step;
		camera->pos.y += camera->dir.y * camera->deplacement_step;
		camera->pos.z += camera->dir.z * camera->deplacement_step;
		recreate_image(state);
	}
	else if (sign == '-')
	{
		camera->pos.x -= camera->dir.x * camera->deplacement_step;
		camera->pos.y -= camera->dir.y * camera->deplacement_step;
		camera->pos.z -= camera->dir.z * camera->deplacement_step;
		recreate_image(state);
	}
}

static void	rotate_camera(t_state *state, t_camera *camera, char sign)
{
	t_vector2d	rotator;

	if (sign == '+')
		rotator = ft_set_vector2d(0, ft_deg_to_rad(camera->angle_step));
	else if (sign == '-')
		rotator = ft_set_vector2d(0, -ft_deg_to_rad(camera->angle_step));
	else
		rotator = ft_init_vector2d(0);
	camera->dir = ft_rotate_vector3d(camera->dir, rotator);
	camera->x_axis = ft_rotate_vector3d(camera->x_axis, rotator);
	camera->y_axis = ft_rotate_vector3d(camera->y_axis, rotator);
	recreate_image(state);
}

static int	key_pressed(int keycode, t_state *state)
{
	if (keycode == K_ESC)
		exit_program(state, EXIT_SUCCESS);
	if (keycode == UP_ARROW_KEY)
		modify_step_size(state, '+');
	if (keycode == DOWN_ARROW_KEY)
		modify_step_size(state, '-');
	if (keycode == RIGHT_ARROW_KEY)
		modify_angle_step_size(state, '+');
	if (keycode == LEFT_ARROW_KEY)
		modify_angle_step_size(state, '-');
	if (keycode == W_KEY)
		move_camera(state, &state->scene.camera, '+');
	if (keycode == S_KEY)
		move_camera(state, &state->scene.camera, '-');
	if (keycode == Q_KEY)
		rotate_camera(state, &state->scene.camera, '+');
	if (keycode == E_KEY)
		rotate_camera(state, &state->scene.camera, '-');
	return (1);
}

void	loop_events(t_state *state)
{
	mlx_hook(state->win, ON_KEYPRESS, 1L << 0, &key_pressed, state);
	mlx_hook(state->win, ON_CLIENTMSG, 0L, &exit_program, state);
	mlx_loop(state->display);
}
