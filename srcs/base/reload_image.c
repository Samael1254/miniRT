#include "minirt_base.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include "mlx.h"
#include <bits/types/struct_timeval.h>
#include <unistd.h>

void	reload_image(t_state *state)
{
	void	*img_to_reload;

	if (state->post_process == PP_NONE)
		img_to_reload = state->img_data.img;
	else
		img_to_reload = state->processed_img.img;
	mlx_put_image_to_window(state->display, state->win, img_to_reload, 0, 0);
	display_fps(state);
	display_help(state);
}

void	recreate_image(t_state *state)
{
	state->start_time = get_time(state);
	mlx_destroy_image(state->display, state->img_data.img);
	state->img_data.img = mlx_new_image(state->display, WIN_X, WIN_Y);
	if (!state->img_data.img)
		error("init_mlx", "failed to create img", state);
	state->img_data.addr = mlx_get_data_addr(state->img_data.img,
			&state->img_data.bp_pixel, &state->img_data.line_len,
			&state->img_data.endian);
	if (!state->img_data.addr)
		error("init_mlx", "failed to retrieve addr", state);
	state->redraw_column = 0;
	state->rendering = true;
	if (state->post_process != PP_NONE)
		post_process(state);
}
