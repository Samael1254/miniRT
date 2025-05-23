/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_graphics.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:09 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 16:14:36 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_GRAPHICS_BONUS_H
# define MINIRT_GRAPHICS_BONUS_H

# include "minirt_defs.h"

// color.c
t_color	scale_color(t_color color, double lambda);
t_color	add_colors(t_color color1, t_color color2);
t_color	lerp_colors(t_color color1, t_color color2, double lambda);
t_color	absorb_colors(t_color color1, t_color color2);

// color_utils.c
t_color	init_color(unsigned char r, unsigned char g, unsigned char b);
t_color	get_sky_color(t_state *state, t_ray ray);

// graphics.c
void	put_pixel(t_img_data *img, t_ivec2 coords, t_color color);
t_color	get_pixel_color(t_img_data texture, t_ivec2 coords);
t_color	get_uv_color(t_img_data texture, t_vec2 uv);

// post_process.c
void	post_process(t_state *state);
t_color	post_process_color(t_color color, t_ivec2 coords,
			enum e_post_process post_process);

// post_process_filters.c
t_color	vignette(t_color color, t_ivec2 coords);
t_color	sepia_tone(t_color color);
t_color	vignette(t_color color, t_ivec2 coords);
t_color	negative(t_color color);
t_color	gamma_correction(t_color color);
t_color	posterization(t_color color);
t_color	saturation_boost(t_color color);
t_color	scanlines(t_color color, t_ivec2 coords);
t_color	gray_tone(t_color color);

// post_process_utils.c
t_vec3	ldr_to_hdr_color(t_color ldr);
t_color	hdr_to_ldr_color(t_vec3 hdr);

#endif // !MINIRT_GRAPHICS_BONUS_H
