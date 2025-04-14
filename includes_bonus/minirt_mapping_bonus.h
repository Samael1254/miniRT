/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_mapping_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:09 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:09 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MAPPING_BONUS_H
# define MINIRT_MAPPING_BONUS_H

# include "ft_algebra.h"
# include "minirt_defs_bonus.h"

t_vec2	uv_at_point(t_object object, t_vec3 point, t_vec3 normal);
t_vec3	blend_normal_map(t_vec2 uv, t_vec3 normal, t_material material);

// Object mapping

t_vec2	sphere_mapping(t_vec3 normal);
t_vec2	cylinder_mapping(t_cylinder cylinder, t_vec3 point, t_vec3 normal);
t_vec2	cone_mapping(t_cone cone, t_vec3 point, t_vec3 normal);
t_vec2	plane_mapping(t_plane plane, t_vec3 point, t_vec3 normal);
t_vec2	triangle_mapping(t_triangle triangle, t_vec3 point);

// Mapping utils

t_vec3	get_ref_vec(t_vec3 normal);
t_vec2	clamp_uv(t_vec2 uv);
t_vec2	interpolate_triangle_data2d(t_vec3 vertices[3], t_vec3 point,
			t_vec2 data[3]);
t_vec3	interpolate_triangle_data3d(t_vec3 vertices[3], t_vec3 point,
			t_vec3 data[3]);

#endif
