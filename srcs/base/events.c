#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>

int	key_pressed(int keycode, t_state *state)
{
	if (keycode == K_ESC)
	{
		info(NULL, "close program");
		exit_program(state, EXIT_SUCCESS);
	}
	return (1);
}

void	loop_events(t_state *state)
{
	mlx_hook(state->win, ON_KEYPRESS, 1L << 0, &key_pressed, state);
	mlx_hook(state->win, ON_CLIENTMSG, 0L, &exit_program, state);
	mlx_loop(state->display);
}
