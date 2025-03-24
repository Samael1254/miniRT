#include "minirt_defs_bonus.h"
#include <stdio.h>

void	modify_step_size(t_state *state, char sign)
{
	if (sign == '+' && state->scene.camera.deplacement_step < 120)
	{
		state->scene.camera.deplacement_step += 5;
		printf("Increase of the step deplacement of the camera. Value = %d\n",
				state->scene.camera.deplacement_step);
	}
	else if (sign == '+')
	{
		printf("Impossible to increase deplacement step. Maximum: 120.");
		printf(" Actual value: %d\n", state->scene.camera.deplacement_step);
	}
	if (sign == '-' && state->scene.camera.deplacement_step > 5)
	{
		state->scene.camera.deplacement_step -= 5;
		printf("Decrease of the step deplacement of the camera. Value = %d\n",
				state->scene.camera.deplacement_step);
	}
	else if (sign == '-')
	{
		printf("Impossible to decrease deplacement step. Minimum: 5.");
		printf(" Actual value: %d\n", state->scene.camera.deplacement_step);
	}
}

void	modify_angle_step_size(t_state *state, char sign)
{
	if (sign == '+' && state->scene.camera.angle_step < 180)
	{
		state->scene.camera.angle_step += 15;
		printf("Increase of the step angle of the camera. Value = %d\n",
				state->scene.camera.angle_step);
	}
	else if (sign == '+')
	{
		printf("Impossible to increase angle step. Maximum: 180.");
		printf(" Actual value: %d\n", state->scene.camera.angle_step);
	}
	if (sign == '-' && state->scene.camera.angle_step > 15)
	{
		state->scene.camera.angle_step -= 15;
		printf("Decrease of the step angle of the camera. Value = %d\n",
				state->scene.camera.angle_step);
	}
	else if (sign == '-')
	{
		printf("Impossible to decrease angle step. Minimum: 15.");
		printf(" Actual value: %d\n", state->scene.camera.angle_step);
	}
}
