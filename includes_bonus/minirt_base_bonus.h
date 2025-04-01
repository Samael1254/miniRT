#ifndef MINIRT_BASE_BONUS
# define MINIRT_BASE_BONUS

# include "minirt_defs_bonus.h"

// events_bonus.c

void			move_camera(t_state *state, t_camera *camera,
					enum e_keycode key);
void			loop_events(t_state *state);

// events_bonus_utils.c

void			modify_step_size(t_state *state, char sign);
void			modify_rot_step_size(t_state *state, char sign);
void			recreate_image(t_state *state);
int				on_mouse_moov(enum e_keycode key, int x, int y, t_state *state);
int				end_hold_alt_hook(int button, t_state *state);

// exit_program_utils.c

int				exit_program(t_state *state, int status);

// init_state_bonus.c

void			init_state(t_state *state, char *filename);

// time_bonus.c

long			get_time_diff(struct timeval time, struct timeval start_time);
struct timeval	get_time(t_state *state);

#endif // !MINIRT_BASE_BONUS
