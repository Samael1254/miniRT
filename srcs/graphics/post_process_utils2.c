/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_graphics.h"

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
