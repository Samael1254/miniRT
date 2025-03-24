#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include "mlx.h"
#include <stdlib.h>

void	ray_tracing(t_state *state)
{
	info(NULL, "ray tracing...");
	shoot_rays(state);
	info(NULL, "rendering...");
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
}
