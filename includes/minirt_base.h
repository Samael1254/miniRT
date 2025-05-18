/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_base.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:05 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 16:22:02 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BASE_BONUS_H
# define MINIRT_BASE_BONUS_H

# include "minirt_defs.h"

// events.c

void			move_camera(t_state *state, t_camera *camera,
					enum e_keycode key);
void			loop_events(t_state *state);

// events_utils.c

void			modify_step_size(t_state *state, char sign);
void			modify_rot_step_size(t_state *state, char sign);
void			display_fps(t_state *state);
void			recreate_image(t_state *state);
void			reload_image(t_state *state);
int				on_mouse_moov(enum e_keycode key, int x, int y, t_state *state);
int				end_hold_alt_hook(int button, t_state *state);
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

char			*select_scene(void);

#endif // !MINIRT_BASE_BONUS
