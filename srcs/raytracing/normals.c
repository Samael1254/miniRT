/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs.h"

static t_vec3	sphere_normal(t_sphere sphere, t_vec3 point)
{
	return (ft_normalize_vec3(ft_sub_vec3(point, sphere.pos)));
}

static t_vec3	plane_normal(t_plane plane)
{
	return (plane.normal);
}

static t_vec3	cylinder_normal(t_cylinder cylinder, t_vec3 point)
{
	t_vec3	ba;
	t_vec3	pa;
	double	h;
	double	radius;
	t_vec3	a;

	radius = cylinder.diameter / 2.0;
	ba = ft_scale_vec3(cylinder.height,
			ft_normalize_vec3(cylinder.axis));
	a = ft_sub_vec3(cylinder.pos, ft_scale_vec3(0.5, ba));
	pa = ft_sub_vec3(point, a);
	h = ft_dot_vec3(pa, ba) / ft_dot_vec3(ba, ba);
	if (ft_inff(h, 0))
		return (ft_normalize_vec3(ft_scale_vec3(-1.0, ba)));
	if (ft_supf(h, 1))
		return (ft_normalize_vec3(ba));
	return (ft_normalize_vec3(ft_scale_vec3(1.0 / radius,
				ft_sub_vec3(pa, ft_scale_vec3(h, ba)))));
}

t_vec3	normal_at_point(t_object object, t_vec3 point,
		t_vec3 ray_dir)
{
	t_vec3	normal;

	if (object.type == SPHERE)
		normal = sphere_normal(*(t_sphere *)object.object_r, point);
	else if (object.type == PLANE)
		normal = plane_normal(*(t_plane *)object.object_r);
	else if (object.type == CYLINDER)
		normal = cylinder_normal(*(t_cylinder *)object.object_r, point);
	else
		return (ft_init_vec3(0));
	if (ft_supf(ft_dot_vec3(normal, ray_dir), 0))
		return (ft_scale_vec3(-1, normal));
	return (normal);
}
