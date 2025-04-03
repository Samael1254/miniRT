#include "ft_algebra.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_raytracing_bonus.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	ray_tracing(t_state *state)
{
	t_ivec2	hit;

	info(NULL, "ray tracing...");
	shoot_rays(state);
	hit = hit_box(false, true);
	printf("hit: %d, miss: %d, ratio: %f%%\n", hit.x, hit.y - hit.x,
		(double)hit.x / (double)hit.y * 100);
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
}
