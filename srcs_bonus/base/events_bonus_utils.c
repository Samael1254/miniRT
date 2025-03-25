#include "minirt_defs_bonus.h"
#include <stdio.h>

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
