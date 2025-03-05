#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>

static void	free_mlx(t_state *state)
{
	if (!state->display)
		return ;
	if (state->img_data.img)
		mlx_destroy_image(state->display, state->img_data.img);
	if (state->win)
		mlx_destroy_window(state->display, state->win);
	mlx_destroy_display(state->display);
	free(state->display);
}

int	exit_program(t_state *state, int status)
{
	if (state)
		free_mlx(state);
	exit(status);
}
