#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_raytracing_bonus.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	ray_tracing(t_state *state)
{
	info(NULL, "ray tracing...");
	shoot_rays(state);
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
}
