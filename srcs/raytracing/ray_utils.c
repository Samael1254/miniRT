/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 17:43:34 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include "minirt_intersections.h"
#include "minirt_light.h"
#include "minirt_raytracing.h"
#include <pthread.h>

static t_color	average_colors(t_color *colors)
{
	int		i;
	int		sum_r;
	int		sum_g;
	int		sum_b;
	t_color	color;

	i = 0;
	sum_r = 0;
	sum_g = 0;
	sum_b = 0;
	while (i < AA_LEVEL * AA_LEVEL)
	{
		sum_r += colors[i].r;
		sum_g += colors[i].g;
		sum_b += colors[i].b;
		i++;
	}
	color.r = sum_r / (AA_LEVEL * AA_LEVEL);
	color.g = sum_g / (AA_LEVEL * AA_LEVEL);
	color.b = sum_b / (AA_LEVEL * AA_LEVEL);
	return (color);
}

void	supersampling(t_vec2 rotator, t_ivec2 coords, t_vec2 delta,
		t_state *state)
{
	t_ivec2	sub_coords;
	t_vec2	offset;
	t_vec2	sub_rotator;
	t_color	colors[AA_LEVEL * AA_LEVEL];

	sub_coords.x = 0;
	while (sub_coords.x < AA_LEVEL)
	{
		sub_coords.y = 0;
		while (sub_coords.y < AA_LEVEL)
		{
			offset.x = (sub_coords.x + 0.5) / AA_LEVEL;
			offset.y = (sub_coords.y + 0.5) / AA_LEVEL;
			sub_rotator.x = rotator.x + delta.x * (offset.x - 0.5);
			sub_rotator.y = rotator.y + delta.y * (offset.y - 0.5);
			colors[2 * sub_coords.x + sub_coords.y++] = trace_ray(sub_rotator,
					coords, state);
		}
		sub_coords.x++;
	}
	put_pixel(&state->img_data, coords, average_colors(colors));
}

static t_ray	init_ray(t_camera camera, t_vec2 rotator)
{
	t_ray	ray;
	double	m_rot_x[4][4];
	double	m_rot_y[4][4];

	ft_set_rotation_mat4(m_rot_y, rotator.y, camera.y_axis);
	ray.direction = ft_4dto3d_vector(ft_mat_vec_product4(m_rot_y,
				ft_3dto4d_vector(camera.dir)));
	camera.x_axis = ft_4dto3d_vector(ft_mat_vec_product4(m_rot_y,
				ft_3dto4d_vector(camera.x_axis)));
	ft_set_rotation_mat4(m_rot_x, rotator.x, camera.x_axis);
	ray.direction = ft_4dto3d_vector(ft_mat_vec_product4(m_rot_x,
				ft_3dto4d_vector(ray.direction)));
	ray.origin = camera.pos;
	ray.refraction = AIR_REFRACTION;
	return (ray);
}

t_color	trace_ray(t_vec2 rotator, t_ivec2 coords, t_state *state)
{
	t_ray			ray;
	t_intersection	inter;
	t_color			color;

	ray = init_ray(state->scene.camera, rotator);
	inter = intersect_scene(ray, state);
	color = phong_illumination(state, inter, ray);
	if (!state->toggle_aa)
		put_pixel(&state->img_data, coords, color);
	return (color);
}

void	ft_join_threads(t_state *state, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
		if (pthread_join(threads[i++], NULL) != 0)
			error("pthread_join", "crash", state);
}
