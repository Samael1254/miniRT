/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_filters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 15:56:45 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_graphics.h"
#include <math.h>

t_color	vignette(t_color color, t_ivec2 coords)
{
	double			vignette_scale;
	const double	intensity = 0.5;
	const double	dx = (double)(coords.x - WIN_X / 2.) / (double)(WIN_X / 2.);
	const double	dy = (double)(coords.y - WIN_Y / 2.) / (double)(WIN_Y / 2.);

	vignette_scale = 1 - (dx * dx + dy * dy) * intensity;
	return (scale_color(color, vignette_scale));
}

t_color	sepia_tone(t_color color)
{
	t_vec3	hdr;
	t_vec3	sepia;

	hdr = ldr_to_hdr_color(color);
	sepia.x = hdr.x * .393 + hdr.y * .769 + hdr.z * .189;
	sepia.y = hdr.x * .349 + hdr.y * .686 + hdr.z * .168;
	sepia.z = hdr.x * .272 + hdr.y * .534 + hdr.z * .131;
	return (hdr_to_ldr_color(sepia));
}

t_color	negative(t_color color)
{
	t_color	neg;

	neg.r = 255 - color.r;
	neg.g = 255 - color.g;
	neg.b = 255 - color.b;
	return (neg);
}

t_color	gamma_correction(t_color color)
{
	const double	gamma_inv = 1 / 1.3;
	t_color			corrected_color;

	corrected_color.r = (unsigned char)(pow((double)color.r / 255, gamma_inv)
			* 255);
	corrected_color.g = (unsigned char)(pow((double)color.g / 255, gamma_inv)
			* 255);
	corrected_color.b = (unsigned char)(pow((double)color.b / 255, gamma_inv)
			* 255);
	return (corrected_color);
}

t_color	gray_tone(t_color color)
{
	double	gray;

	gray = ft_dot_vec3(ldr_to_hdr_color(color), ft_set_vec3(0.299, 0.587,
				0.114));
	return (hdr_to_ldr_color(ft_init_vec3(gray)));
}

t_color	scanlines(t_color color, t_ivec2 coords)
{
	if ((coords.y / 4) % 2)
		return (color);
	return (scale_color(color, 0.7));
}

t_color	saturation_boost(t_color color)
{
	double			intensity;
	const double	saturation = 1.5;

	intensity = ft_dot_vec3(ldr_to_hdr_color(color), ft_set_vec3(0.2126, 0.7152,
				0.0722));
	return (lerp_colors(color, hdr_to_ldr_color(ft_init_vec3(intensity)),
			saturation));
}

t_color	posterization(t_color color)
{
	const int	levels = 7;
	t_vec3		hdr;

	hdr = ft_scale_vec3(levels, ldr_to_hdr_color(color));
	hdr.x = floor(hdr.x) / (double)levels;
	hdr.y = floor(hdr.y) / (double)levels;
	hdr.z = floor(hdr.z) / (double)levels;
	return (hdr_to_ldr_color(hdr));
}
