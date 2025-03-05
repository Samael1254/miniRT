#include "minirt.h"
#include <stdlib.h>

int	key_pressed(int keycode, t_state *state)
{
	if (keycode == K_ESC)
		exit_program(state, EXIT_SUCCESS);
	return (1);
}
