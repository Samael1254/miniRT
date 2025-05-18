/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 15:57:32 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt_graphics.h"

t_vec3	ldr_to_hdr_color(t_color ldr)
{
	t_vec3	hdr;

	hdr.x = (double)ldr.r / 255;
	hdr.y = (double)ldr.g / 255;
	hdr.z = (double)ldr.b / 255;
	return (hdr);
}

t_color	hdr_to_ldr_color(t_vec3 hdr)
{
	t_color	ldr;

	ldr.r = (unsigned char)ft_clampf(hdr.x * 255, 0, 255);
	ldr.g = (unsigned char)ft_clampf(hdr.y * 255, 0, 255);
	ldr.b = (unsigned char)ft_clampf(hdr.z * 255, 0, 255);
	return (ldr);
}
