/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_mapping_bonus.h"

t_vec3	sphere_normal(t_sphere sphere, t_vec3 point)
{
	return (ft_normalize_vec3(ft_sub_vec3(point, sphere.pos)));
}

t_vec3	plane_normal(t_plane plane)
{
	return (plane.normal);
}

t_vec3	cone_normal(t_cone cone, t_vec3 point)
{
	t_vec3	cp;
	t_vec3	tan;

	cp = ft_sub_vec3(point, cone.pos);
	tan = ft_cross_vec3(cone.axis, cp);
	return (ft_normalize_vec3(ft_cross_vec3(cp, tan)));
}

t_vec3	triangle_normal(t_triangle triangle, t_vec3 point)
{
	t_vec3	normal;

	normal = interpolate_triangle_data3d(triangle.vertices, point,
			triangle.normals);
	return (normal);
}

t_vec3	cylinder_normal(t_cylinder cylinder, t_vec3 point)
{
	t_vec3	ba;
	t_vec3	pa;
	double	h;
	double	radius;
	t_vec3	a;

	radius = cylinder.diameter / 2.0;
	ba = ft_scale_vec3(cylinder.height, ft_normalize_vec3(cylinder.axis));
	a = ft_sub_vec3(cylinder.pos, ft_scale_vec3(0.5, ba));
	pa = ft_sub_vec3(point, a);
	h = ft_dot_vec3(pa, ba) / ft_dot_vec3(ba, ba);
	if (ft_inff(h, 0))
		return (ft_normalize_vec3(ft_scale_vec3(1.0, ba)));
	if (ft_supf(h, 1))
		return (ft_normalize_vec3(ba));
	return ((ft_scale_vec3(1.0 / radius, ft_sub_vec3(pa,
					ft_scale_vec3(h, ba)))));
}
