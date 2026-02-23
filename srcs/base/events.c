#include "minirt_base.h"
#include "minirt_defs.h"
#include "minirt_events.h"
#include "minirt_raytracing.h"
#include "mlx.h"

int mouse_clicked(enum e_keycode button, int x, int y, t_state *state)
{
	if (button == SCROLL_UP)
		move_camera(state, &state->scene.camera, SCROLL_UP);
	if (button == SCROLL_DOWN)
		move_camera(state, &state->scene.camera, SCROLL_DOWN);
	if (button == LEFT_CLICK)
		get_clicked_object_info(x, y, state);
	return (0);
}

void loop_events(t_state *state)
{
	mlx_hook(state->win, ON_KEYPRESS, 1L << 0, (void *)key_pressed, state);
	mlx_hook(state->win, ON_KEYRELEASE, 1L << 1, (void *)key_released, state);
	mlx_hook(state->win, ON_BUTTONPRESS, 1L << 2, (void *)mouse_clicked, state);
	mlx_hook(state->win, ON_CLIENTMSG, 0L, (void *)exit_program, state);
	mlx_loop_hook(state->display, (void *)render_loop, state);
	mlx_loop(state->display);
}
