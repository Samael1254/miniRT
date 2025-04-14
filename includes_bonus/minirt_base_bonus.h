#ifndef MINIRT_BASE_BONUS_H
# define MINIRT_BASE_BONUS_H

# include "minirt_defs_bonus.h"

// events_bonus.c

void			move_camera(t_state *state, t_camera *camera,
					enum e_keycode key);
void			loop_events(t_state *state);

// events_bonus_utils.c

void			modify_step_size(t_state *state, char sign);
void			modify_rot_step_size(t_state *state, char sign);
void			recreate_image(t_state *state);
void			reload_image(t_state *state);
int				on_mouse_moov(enum e_keycode key, int x, int y, t_state *state);
int				end_hold_alt_hook(int button, t_state *state);
void			display_help(t_state *state);

// events_utils_toggle_bonus.c
void	toggle_lights(t_state *state);
void	toggle_aa(t_state *state);
void	toggle_help(t_state *state);
void	toggle_fps(t_state *state);
void	change_post_processing(t_state *state);


// exit_program_utils.c

int				exit_program(t_state *state, int status);

// init_state_bonus.c

void			init_state(t_state *state, char *filename);

// time_bonus.c

long			get_time_diff(struct timeval time, struct timeval start_time);
struct timeval	get_time(t_state *state);
char			*get_fps_string(long time);

#endif // !MINIRT_BASE_BONUS
