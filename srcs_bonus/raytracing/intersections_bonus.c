#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_mapping_bonus.h"
#include "minirt_normals_bonus.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static t_intersection	make_intersection(t_ray ray, t_object *object,
		double distance_min, t_state *state)
{
	t_intersection	inter;

	if (!ft_in_rangef(distance_min, RAY_REACH_MIN, RAY_REACH_MAX))
	{
		inter.index_mat = 0;
		inter.point = ft_init_vec3(INFINITY);
		inter.normal = ft_init_vec3(0);
		free_triangle_obj(object);
		return (inter);
	}
	inter.index_mat = object->index_mat;
	inter.point = ft_add_vec3(ray.origin, ft_scale_vec3(distance_min,
				ray.direction));
	inter.normal = normal_at_point(*object, inter, ray.direction);
	inter.uv = uv_at_point(*object, inter.point, inter.normal);
	inter.normal = blend_normal_map(inter.uv, inter.normal,
			state->mats_tab[inter.index_mat]);
	free_triangle_obj(object);
	return (inter);
}

static double	intersect_object(t_ray ray, t_object **object)
{
	void	*object_r;

	object_r = (*object)->object_r;
	if ((*object)->type == SPHERE)
		return (intersect_sphere(ray, *(t_sphere *)object_r));
	else if ((*object)->type == PLANE)
		return (intersect_plane(ray, *(t_plane *)object_r));
	else if ((*object)->type == CYLINDER)
		return (intersect_cylinder(ray, *(t_cylinder *)object_r));
	else if ((*object)->type == CONE)
		return (intersect_cone(ray, *(t_cone *)object_r));
	else if ((*object)->type == MESH)
		return (intersect_mesh(ray, (t_mesh *)object_r, object));
	warning("invalid object", "object type not found");
	return (INFINITY);
}

static void	update_distance_and_object(double *distance_min,
		t_object **closest_object, double cur_distance, t_object *cur_object)
{
	*distance_min = cur_distance;
	free_triangle_obj(*closest_object);
	*closest_object = cur_object;
}

t_intersection	intersect_scene(t_ray ray, t_state *state)
{
	double		cur_distance;
	double		distance_min;
	t_object	*cur_object;
	t_object	*closest_object;
	t_list		*iter;

	distance_min = INFINITY;
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
			update_distance_and_object(&distance_min, &closest_object,
				cur_distance, cur_object);
		else
			free_triangle_obj(cur_object);
		iter = iter->next;
	}
	return (make_intersection(ray, closest_object, distance_min, state));
}
