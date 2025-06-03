/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_raytracing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/06/03 18:22:13 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RAYTRACING_BONUS_H
# define MINIRT_RAYTRACING_BONUS_H

# include "minirt_defs.h"

double	vertical_fov_2(double horizontal_fov_2);
void	shoot_rays(t_state *state, int render_index);
int		render_loop(t_state *state);
void	ray_tracing(t_state *state);
t_ray	init_ray(t_camera camera, t_vec2 rotator);
t_color	trace_ray(t_vec2 rotator, t_ivec2 coords, t_state *state);
void	supersampling(t_vec2 rotator, t_ivec2 coords, t_vec2 delta,
			t_state *state);
void	ft_join_threads(t_state *state, pthread_t *threads);

#endif
