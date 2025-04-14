/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_from_one_light_utils_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_light_bonus.h"

t_color	specular_color(t_intersection inter, t_vec3 light_dir, t_vec3 view_dir,
		t_state *state)
{
	t_material	material;

	material = state->mats_tab[inter.index_mat];
	return (scale_color(material.ks, get_specular_term(light_dir, view_dir,
				inter.normal, material)));
}

t_color	ambiant_color(t_ambiant_light a_light, t_material material,
		t_intersection inter)
{
	t_color	color;

	color = material.ka;
	if (material.img_texture.img)
		color = absorb_colors(color, get_pixel_color(material.img_texture,
					inter.uv));
	color = absorb_colors(color, a_light.color);
	return (scale_color(color, a_light.brightness));
}

t_color	diffuse_color(double incidence, t_material material,
		t_intersection inter)
{
	t_color	color;

	color = material.kd;
	if (material.img_texture.img)
		color = absorb_colors(color, get_pixel_color(material.img_texture,
					inter.uv));
	incidence = ft_clampf(incidence, 0, 1);
	return (scale_color(color, incidence));
}
