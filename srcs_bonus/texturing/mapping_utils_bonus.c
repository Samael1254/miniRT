/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_math.h"
#include <math.h>

t_vec3	get_ref_vec(t_vec3 normal)
{
	t_vec3	r;

	if (ft_supf(fabs(normal.y), 0.999))
		r = ft_set_vec3(0, 0, copysign(1, normal.y));
	else
		r = ft_set_vec3(0, 1, 0);
	return (r);
}

t_vec2	clamp_uv(t_vec2 uv)
{
	uv.x = fmod(uv.x, 1.0f);
	uv.y = fmod(uv.y, 1.0f);
	if (ft_inff(uv.x, 0))
		uv.x = 1 + uv.x;
	if (ft_inff(uv.y, 0))
		uv.y = 1 + uv.y;
	return (uv);
}

static t_vec3	cartesian_to_barycentric3d(t_vec3 vertices[3], t_vec3 point)
{
	t_vec3	bary;
	double	areas[3];
	t_vec3	edges[2];
	t_vec3	vectors[3];

	edges[0] = ft_sub_vec3(vertices[1], vertices[0]);
	edges[1] = ft_sub_vec3(vertices[2], vertices[0]);
	vectors[0] = ft_sub_vec3(point, vertices[0]);
	vectors[1] = ft_sub_vec3(point, vertices[1]);
	vectors[2] = ft_sub_vec3(point, vertices[2]);
	areas[0] = ft_vec3_norm(ft_cross_vec3(edges[0], edges[1]));
	areas[1] = ft_vec3_norm(ft_cross_vec3(vectors[1], vectors[2]));
	areas[2] = ft_vec3_norm(ft_cross_vec3(vectors[2], vectors[0]));
	bary.x = areas[1] / areas[0];
	bary.y = areas[2] / areas[0];
	bary.z = 1 - bary.x - bary.y;
	return (bary);
}

t_vec3	interpolate_triangle_data3d(t_vec3 vertices[3], t_vec3 point,
		t_vec3 data[3])
{
	t_vec3	bary;
	t_vec3	lerp;

	bary = cartesian_to_barycentric3d(vertices, point);
	lerp.x = bary.x * data[0].x + bary.y * data[1].x + bary.z * data[2].x;
	lerp.y = bary.x * data[0].y + bary.y * data[1].y + bary.z * data[2].y;
	lerp.z = bary.x * data[0].z + bary.y * data[1].z + bary.z * data[2].z;
	return (lerp);
}

t_vec2	interpolate_triangle_data2d(t_vec3 vertices[3], t_vec3 point,
		t_vec2 data[3])
{
	t_vec3	bary;
	t_vec2	lerp;

	bary = cartesian_to_barycentric3d(vertices, point);
	lerp.x = bary.x * data[0].x + bary.y * data[1].x + bary.z * data[2].x;
	lerp.y = bary.x * data[0].y + bary.y * data[1].y + bary.z * data[2].y;
	return (lerp);
}
