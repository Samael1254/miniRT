/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "minirt_defs.h"
#include "minirt_graphics.h"
#include "minirt_mapping.h"

static t_vec3	color_to_normal(t_color color)
{
	t_vec3	normal;

	normal.x = (double)color.r / 127.5 - 1;
	normal.y = (double)color.g / 127.5 - 1;
	normal.z = (double)color.b / 127.5 - 1;
	return (normal);
}

static t_vec3	tangent_to_world(t_vec3 normal_tx, t_vec3 normal_world)
{
	t_vec3	r;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	new_normal;

	r = get_ref_vec(normal_world);
	tangent = ft_normalize_vec3(ft_cross_vec3(r, normal_tx));
	bitangent = ft_normalize_vec3(ft_cross_vec3(normal_tx, tangent));
	new_normal = ft_add_vec3(ft_add_vec3(ft_scale_vec3(-(normal_tx.x), tangent),
				ft_scale_vec3(-(normal_tx.y), bitangent)),
			ft_scale_vec3(normal_tx.z, normal_world));
	new_normal = ft_normalize_vec3(new_normal);
	return (new_normal);
}

t_vec3	blend_normal_map(t_vec2 uv, t_vec3 normal, t_material material)
{
	t_vec3	normal_tx;

	if (!material.img_normal.img)
		return (normal);
	normal_tx = color_to_normal(get_uv_color(material.img_normal, uv));
	return (tangent_to_world(normal_tx, normal));
}
