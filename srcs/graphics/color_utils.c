/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_defs.h"
#include "minirt_graphics.h"
#include "minirt_light.h"

t_color	init_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 100;
	return (color);
}

t_color	get_sky_color(t_state *state, t_ray ray)
{
	t_color	sky_color;
	t_list	*iter;

	sky_color = lerp_colors(state->scene.sky.top, state->scene.sky.bottom,
			(ray.direction.y + 1) / 2);
	if (!state->toggle_lights)
		return (sky_color);
	iter = state->scene.lights;
	while (iter)
	{
		sky_color = add_colors(sky_color,
				trace_point_light(*(t_point_light *)iter->data, ray));
		iter = iter->next;
	}
	return (sky_color);
}
