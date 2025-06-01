#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_bvh.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_intersections.h"
#include "minirt_raytracing.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void	get_click_info(int x, int y, t_state *state)
{
	t_vec2			rotator;
	t_vec2			delta;
	t_ray			ray;
	t_intersection	inter;

	delta.y = 2 * state->scene.camera.fov_2 / WIN_X;
	delta.x = 2 * vertical_fov_2(state->scene.camera.fov_2) / WIN_Y;
	rotator.x = vertical_fov_2(state->scene.camera.fov_2) - delta.x * y;
	rotator.y = state->scene.camera.fov_2 - x * delta.y;
	ray = init_ray(state->scene.camera, rotator);
	inter = intersect_scene(ray, state);
	printf("contact point: %.2f, %.2f, %.2f\n", inter.point.x, inter.point.y,
		inter.point.z);
}

t_object	*get_intersected_object(t_ray ray, t_state *state)
{
	double		cur_distance;
	double		distance_min;
	t_object	*cur_object;
	t_object	*closest_object;
	t_list		*iter;

	distance_min = RAY_REACH_MAX;
	closest_object = NULL;
	iter = state->scene.objects;
	while (iter)
	{
		cur_object = (t_object *)iter->data;
		cur_distance = intersect_object(ray, &cur_object);
		if (isnan(cur_distance))
			error("malloc failed", "in face_to_triangle", state);
		if (ft_in_rangef(cur_distance, RAY_REACH_MIN, distance_min)
			&& state->mats_tab[cur_object->index_mat].kd.a != 0)
		{
			distance_min = cur_distance;
			free_triangle_obj(closest_object);
			closest_object = cur_object;
		}
		else
			free_triangle_obj(cur_object);
		iter = iter->next;
	}
	return (closest_object);
}

static t_object	*get_clicked_object(int x, int y, t_state *state)
{
	t_vec2	rotator;
	t_vec2	delta;
	t_ray	ray;

	delta.y = 2 * state->scene.camera.fov_2 / WIN_X;
	delta.x = 2 * vertical_fov_2(state->scene.camera.fov_2) / WIN_Y;
	rotator.x = vertical_fov_2(state->scene.camera.fov_2) - delta.x * y;
	rotator.y = state->scene.camera.fov_2 - x * delta.y;
	ray = init_ray(state->scene.camera, rotator);
	return (get_intersected_object(ray, state));
}

void	get_clicked_object_info(int x, int y, t_state *state)
{
	const t_object	*object;

	object = get_clicked_object(x, y, state);
	printf("type: ");
	if (!object)
	{
		printf("none\n");
		return ;
	}
	switch (object->type)
	{
	case SPHERE:
		printf("sphere\n");
		break ;
	case PLANE:
		printf("plane\n");
		break ;
	case CYLINDER:
		printf("cylinder\n");
		break ;
	case CONE:
		printf("cone\n");
		break ;
	case TRIANGLE:
		printf("mesh\n");
		break ;
	default:
		printf("other\n");
		break ;
	}
}
