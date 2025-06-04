#include "minirt_base.h"
#include <stdio.h>

void	rotate_camera(t_state *state, t_camera *camera, enum e_keycode keycode)
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
