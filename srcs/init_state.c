#include "minirt.h"
#include "mlx.h"

static void	init_mlx(t_state *state)
{
	state->display = mlx_init();
	if (!state->display)
		fatal_error("init_mlx", "failed to create display", state);
	state->win = mlx_new_window(state->display, WIN_X, WIN_Y, "miniRT");
	if (!state->win)
		fatal_error("init_mlx", "failed to create window", state);
}
