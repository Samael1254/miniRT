#include "minirt.h"
#include "minirt_defs.h"
#include "mlx.h"
#include <stddef.h>

static void	init_mlx(t_state *state)
{
	state->display = mlx_init();
	if (!state->display)
		error("init_mlx", "failed to create display", state);
	state->win = mlx_new_window(state->display, WIN_X, WIN_Y, "miniRT");
	if (!state->win)
		error("init_mlx", "failed to create window", state);
	state->img_data.img = mlx_new_image(state->display, WIN_X, WIN_Y);
	if (!state->img_data.img)
		error("init_mlx", "failed to create img", state);
	state->img_data.addr = mlx_get_data_addr(state->img_data.img,
			&state->img_data.bp_pixel, &state->img_data.line_len,
			&state->img_data.endian);
	if (!state->img_data.addr)
		error("init_mlx", "failed to retrieve addr", state);
}

static void	initialize_state(t_state *state)
{
	state->display = NULL;
	state->scene.objects = NULL;
	state->id_list[0] = NULL;
	state->id_list[1] = NULL;
	state->id_list[2] = NULL;
}

void	init_state(t_state *state, char *filename)
{
	initialize_state(state);
	info(NULL, "initialize scene...");
	init_scene(state, filename);
	info(NULL, "initialize mlx...");
	init_mlx(state);
}
