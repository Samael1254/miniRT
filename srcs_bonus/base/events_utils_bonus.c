#include "minirt_defs_bonus.h"
#include "minirt_bonus.h"
#include <stdio.h>
#include "mlx.h"

void	modify_step_size(t_state *state, char sign)
{
	if (sign == '+' && state->scene.camera.move_step < 120)
	{
		state->scene.camera.move_step += 5;
		printf("Increase of the step deplacement of the camera. Value = %d\n",
			state->scene.camera.move_step);
	}
	else if (sign == '+')
	{
		printf("Impossible to increase deplacement step. Maximum: 120.");
		printf(" Actual value: %d\n", state->scene.camera.move_step);
	}
	if (sign == '-' && state->scene.camera.move_step > 5)
	{
		state->scene.camera.move_step -= 5;
		printf("Decrease of the step deplacement of the camera. Value = %d\n",
			state->scene.camera.move_step);
	}
	else if (sign == '-')
	{
		printf("Impossible to decrease deplacement step. Minimum: 5.");
		printf(" Actual value: %d\n", state->scene.camera.move_step);
	}
}

void	modify_rot_step_size(t_state *state, char sign)
{
	if (sign == '+' && state->scene.camera.rot_step < 180)
	{
		state->scene.camera.rot_step += 15;
		printf("Increase of the step angle of the camera. Value = %d\n",
			state->scene.camera.rot_step);
	}
	else if (sign == '+')
	{
		printf("Impossible to increase angle step. Maximum: 180.");
		printf(" Actual value: %d\n", state->scene.camera.rot_step);
	}
	if (sign == '-' && state->scene.camera.rot_step > 15)
	{
		state->scene.camera.rot_step -= 15;
		printf("Decrease of the step angle of the camera. Value = %d\n",
			state->scene.camera.rot_step);
	}
	else if (sign == '-')
	{
		printf("Impossible to decrease angle step. Minimum: 15.");
		printf(" Actual value: %d\n", state->scene.camera.rot_step);
	}
}

void	recreate_image(t_state *state)
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
