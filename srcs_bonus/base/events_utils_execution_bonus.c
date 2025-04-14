#include "mlx.h"
#include "minirt_base_bonus.h"
#include <stdio.h>

void	display_help(t_state *state)
{
	if (!state->toggle_help)
		return ;
	mlx_string_put(state->display, state->win, 20, 20, 0xFFFFFF, "-- HELP --");
	mlx_string_put(state->display, state->win, 20, 40, 0xFFFFFF,
		"Move: WASD");
	mlx_string_put(state->display, state->win, 20, 55, 0xFFFFFF,
		"Zoom: Mouse wheel");
	mlx_string_put(state->display, state->win, 20, 70, 0xFFFFFF,
		"Rotate: ALT + WASD");
	mlx_string_put(state->display, state->win, 20, 85, 0xFFFFFF,
		"Change movement speed: UP/DOWN");
	mlx_string_put(state->display, state->win, 20, 100, 0xFFFFFF,
		"Change rotation speed: LEFT/RIGHT");
	mlx_string_put(state->display, state->win, 20, 115, 0xFFFFFF,
		"Show source light(s): L");
	mlx_string_put(state->display, state->win, 20, 130, 0xFFFFFF,
		"Change post-process: P");
	mlx_string_put(state->display, state->win, 20, 145, 0xFFFFFF,
		"Anti-aliasing: K");
	mlx_string_put(state->display, state->win, 20, 160, 0xFFFFFF,
		"Show FPS: F");
	mlx_string_put(state->display, state->win, 20, 175, 0xFFFFFF,
		"Exit program: ESC");
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
