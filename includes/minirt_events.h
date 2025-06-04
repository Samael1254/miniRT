#ifndef MINIRT_EVENTS_H
# define MINIRT_EVENTS_H

# include "minirt_defs.h"

void	loop_events(t_state *state);

void	move_camera(t_state *state, t_camera *camera, enum e_keycode key);
void	rotate_camera(t_state *state, t_camera *camera, enum e_keycode keycode);

int		key_pressed(enum e_keycode key, t_state *state);

#endif
