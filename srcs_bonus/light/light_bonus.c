/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_list.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_light_bonus.h"
#include <math.h>
#include <stdbool.h>

static void	shade_light_loop(t_state *state, t_intersection *light_inter,
							t_ray *light_ray, t_point_light *light)
{
	double		max_dist;
	t_material	mat;
	double		travel_dist;

	mat = state->mats_tab[light_inter->index_mat];
	max_dist = ft_distance3d(light_ray->origin, light->pos);
	while (light_inter->point.x != INFINITY && mat.transparency > 0)
	{
		travel_dist = ft_distance3d(light_ray->origin, light_inter->point);
		if (travel_dist > max_dist)
			break ;
		light->color = absorb_colors(light->color, scale_color(mat.kd,
					mat.transparency));
		light_ray->origin = light_inter->point;
		*light_inter = intersect_scene(*light_ray, state);
		mat = state->mats_tab[light_inter->index_mat];
	}
}

static t_color	shade_from_one_light(t_intersection inter, t_ray ray,
		t_state *state, t_point_light light)
{
	t_color			color;
	t_ray			light_ray;
	t_intersection	light_inter;

	light_ray.origin = inter.point;
	light_ray.direction = get_light_direction(light_ray, light);
	light_inter = intersect_scene(light_ray, state);
	shade_light_loop(state, &light_inter, &light_ray, &light);
	if (ft_supf(ft_distance3d(light_ray.origin, light.pos),
			ft_distance3d(light_ray.origin, light_inter.point)))
		return (init_color(0, 0, 0));
	color = diffuse_color(ft_dot_vec3(light_ray.direction, inter.normal),
			state->mats_tab[inter.index_mat], inter);
	color = add_colors(color, specular_color(inter, light_ray.direction,
				ray.direction, state));
	color = absorb_colors(color, scale_color(light.color, light.brightness
				* get_dist_attenuation(inter.point, light.pos)));
	return (color);
}

static t_color	shade_point_light(t_intersection inter, t_ray ray,
		t_state *state, t_point_light light)
{
	t_ray			light_ray;
	t_intersection	light_inter;

	if (!state->toggle_lights)
		return (init_color(0, 0, 0));
	light_ray.origin = inter.point;
	light_ray.direction = get_light_direction(light_ray, light);
	light_inter = intersect_scene(light_ray, state);
	shade_light_loop(state, &light_inter, &light_ray, &light);
	if (ft_supf(ft_distance3d(light_ray.origin, light.pos),
			ft_distance3d(light_ray.origin, light_inter.point)))
		return (init_color(0, 0, 0));
	return (trace_point_light(light, ray));
}

t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray)
{
	t_color		color;
	t_color		lights_color;
	t_list		*iter;
	t_material	mat;

	if (inter.point.x == INFINITY)
		return (get_sky_color(state, ray));
	mat = state->mats_tab[inter.index_mat];
	color = ambiant_color(state->scene.a_light, mat, inter);
	lights_color = init_color(0, 0, 0);
	iter = state->scene.lights;
	while (iter)
	{
		color = add_colors(color, shade_from_one_light(inter, ray, state,
					*(t_point_light *)iter->data));
		lights_color = add_colors(lights_color, shade_point_light(inter, ray,
					state, *(t_point_light *)iter->data));
		iter = iter->next;
	}
	color = refract_reflect_rays(color, ray, inter, state);
	color = add_colors(color, lights_color);
	return (color);
}
