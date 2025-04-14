/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_light_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_light_bonus.h"
#include <math.h>
#include <stdbool.h>

static t_color	reflected_ray(t_ray ray, t_intersection inter, t_state *state,
		int bounce_max)
{
	t_ray			reflected_ray;
	t_intersection	new_inter;
	t_material		mat;

	if (bounce_max == -1)
		bounce_max = BOUNCE_MAX;
	mat = state->mats_tab[inter.index_mat];
	if (inter.bounces >= (unsigned int)bounce_max)
		return (scale_color(mat.kd, 1 - mat.reflectance));
	reflected_ray.origin = inter.point;
	reflected_ray.direction = get_reflection_dir(ray.direction, inter.normal);
	reflected_ray.refraction = ray.refraction;
	new_inter = intersect_scene(reflected_ray, state);
	new_inter.bounces = inter.bounces + 1;
	return (phong_illumination(state, new_inter, reflected_ray));
}

double	fresnel_reflectance(double n1, double n2, t_vec3 dir, t_vec3 normal)
{
	const double	r0 = pow((n1 - n2) / (n1 + n2), 2);
	const double	cos1 = -ft_dot_vec3(normal, dir);

	return (r0 + (1 - r0) * pow(1 - cos1, 5));
}

static t_color	refracted_ray(t_ray ray, t_intersection inter, t_state *state)
{
	t_ray			refracted_ray;
	t_intersection	new_inter;
	t_material		mat;

	if (inter.bounces >= BOUNCE_MAX)
		return (scale_color(mat.kd, 1 - mat.transparency));
	mat = state->mats_tab[inter.index_mat];
	refracted_ray.origin = inter.point;
	refracted_ray.direction = get_refraction_dir(ray.direction, inter.normal,
			ray.refraction, mat.refraction);
	if (ray.refraction == mat.refraction)
		refracted_ray.refraction = AIR_REFRACTION;
	else
		refracted_ray.refraction = mat.refraction;
	new_inter = intersect_scene(refracted_ray, state);
	new_inter.bounces = inter.bounces + 1;
	return (phong_illumination(state, new_inter, refracted_ray));
}

t_color	refract_reflect_rays(t_color color, t_ray ray, t_intersection inter,
		t_state *state)
{
	double				f;
	t_color				diffuse;
	const t_material	mat = state->mats_tab[inter.index_mat];

	if (mat.transparency > 0)
	{
		diffuse = color;
		f = fresnel_reflectance(ray.refraction, mat.refraction, ray.direction,
				inter.normal);
		color = lerp_colors(reflected_ray(ray, inter, state, 1),
				refracted_ray(ray, inter, state), f);
		if (mat.transparency < 1)
			color = lerp_colors(absorb_colors(diffuse, color), color, 1
					- mat.transparency);
	}
	else if (mat.reflectance > 0)
		color = lerp_colors(absorb_colors(reflected_ray(ray, inter, state, -1),
					mat.ks), color, mat.reflectance);
	return (color);
}
