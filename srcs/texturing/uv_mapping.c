/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_defs.h"
#include "minirt_mapping.h"

t_vec2	uv_at_point(t_object object, t_vec3 point, t_vec3 normal)
{
	t_vec2	uv;

	if (object.type == SPHERE)
		uv = sphere_mapping(normal);
	else if (object.type == PLANE)
		uv = plane_mapping(*(t_plane *)object.object_r, point, normal);
	else if (object.type == CYLINDER)
		uv = cylinder_mapping(*(t_cylinder *)object.object_r, point, normal);
	else if (object.type == CONE)
		uv = cone_mapping(*(t_cone *)object.object_r, point, normal);
	else if (object.type == TRIANGLE)
		uv = triangle_mapping(*(t_triangle *)object.object_r, point);
	else
		return (ft_init_vec2(0));
	uv.y = 1 - uv.y;
	return (uv);
}
