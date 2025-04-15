/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs.h"
#include "minirt_normals.h"

t_vec3	normal_at_point(t_object object, t_intersection inter, t_vec3 ray_dir)
{
	t_vec3	normal;

	if (object.type == SPHERE)
		normal = sphere_normal(*(t_sphere *)object.object_r, inter.point);
	else if (object.type == PLANE)
		normal = plane_normal(*(t_plane *)object.object_r);
	else if (object.type == CYLINDER)
		normal = cylinder_normal(*(t_cylinder *)object.object_r, inter.point);
	else if (object.type == CONE)
		normal = cone_normal(*(t_cone *)object.object_r, inter.point);
	else if (object.type == TRIANGLE)
		normal = triangle_normal(*(t_triangle *)object.object_r, inter.point);
	else
		return (ft_init_vec3(0));
	if (ft_supf(ft_dot_vec3(normal, ray_dir), 0))
		normal = ft_scale_vec3(-1, normal);
	return (normal);
}
