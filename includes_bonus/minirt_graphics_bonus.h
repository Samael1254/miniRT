/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_graphics_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:09 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:09 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_GRAPHICS_BONUS_H
# define MINIRT_GRAPHICS_BONUS_H

# include "minirt_defs_bonus.h"

t_color	post_process(t_color color, t_ivec2 coords, const t_state *state);

// color_bonus.c
t_color	scale_color(t_color color, double lambda);
t_color	add_colors(t_color color1, t_color color2);
t_color	lerp_colors(t_color color1, t_color color2, double lambda);
t_color	absorb_colors(t_color color1, t_color color2);

// color_utils_bonus.c
t_color	init_color(unsigned char r, unsigned char g, unsigned char b);
t_color	get_sky_color(t_state *state, t_ray ray);

// graphics_bonus.c
void	put_pixel(t_img_data *img, t_ivec2 coords, t_color color);
t_color	get_pixel_color(t_img_data texture, t_vec2 uv);

// post_process_utils2_bonus.c
t_color	vignette(t_color color, t_ivec2 coords);
t_color	sepia_tone(t_color color);

// post_process_utils_bonus.c
t_color	vignette(t_color color, t_ivec2 coords);
t_color	negative(t_color color);
t_color	gamma_correction(t_color color);
t_vec3	ldr_to_hdr_color(t_color ldr);
t_color	hdr_to_ldr_color(t_vec3 hdr);

#endif // !MINIRT_GRAPHICS_BONUS_H
