/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_raytracing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 19:04:45 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RAYTRACING_BONUS_H
# define MINIRT_RAYTRACING_BONUS_H

# include "minirt_defs.h"
# include <pthread.h>

void	shoot_rays(t_state *state, int render_index);
int		render_loop(t_state *state);
void	ray_tracing(t_state *state);
t_color	trace_ray(t_vec2 rotator, t_ivec2 coords, t_state *state);
void	supersampling(t_vec2 rotator, t_ivec2 coords, t_vec2 delta,
			t_state *state);
void	ft_join_threads(t_state *state, pthread_t *threads);

#endif
