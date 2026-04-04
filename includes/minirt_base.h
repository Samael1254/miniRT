#ifndef MINIRT_BASE_BONUS_H
# define MINIRT_BASE_BONUS_H

# include "minirt_defs.h"

// events.c

// events_utils.c

void			modify_step_size(t_state *state, char sign);
void			modify_rot_step_size(t_state *state, char sign);
void			display_fps(t_state *state);
void			recreate_image(t_state *state);
void			reload_image(t_state *state);
int				mouse_clicked(enum e_keycode button, int x, int y, t_state *state);
int				key_released(int button, t_state *state);
void			display_help(t_state *state);

// events_utils_toggle.c
void			toggle_lights(t_state *state);
void			toggle_aa(t_state *state);
void			toggle_help(t_state *state);
void			toggle_fps(t_state *state);
void			change_post_processing(t_state *state);

// exit_program_utils.c

int				exit_program(t_state *state, int status);

// init_state.c

void			init_state(t_state *state, char *filename);

// time.c

long			get_time_diff(struct timeval time, struct timeval start_time);
struct timeval	get_time(t_state *state);
char			*get_fps_string(long time);

void			get_clicked_object_info(int x, int y, t_state *state);

char			*select_scene(void);

#endif // !MINIRT_BASE_BONUS
