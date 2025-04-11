#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_light_bonus.h"
#include <stdbool.h>

t_color	reflected_ray(t_ray ray, t_intersection inter, t_state *state)
{
	t_ray			reflected_ray;
	t_intersection	new_inter;

	if (inter.bounces >= BOUNCE_MAX)
		return (init_color(255, 255, 255));
	reflected_ray.origin = inter.point;
	reflected_ray.direction = get_reflection_dir(ray.direction, inter.normal);
	new_inter = intersect_scene(reflected_ray, state);
	new_inter.bounces = inter.bounces + 1;
	return (phong_illumination(state, new_inter, reflected_ray));
}

t_color	refracted_ray(t_ray ray, t_intersection inter, t_state *state)
{
	t_ray			refracted_ray;
	t_intersection	new_inter;
	t_material		mat;

	mat = state->mats_tab[inter.index_mat];
	refracted_ray.origin = inter.point;
	refracted_ray.direction = get_refraction_dir(ray.direction, inter.normal,
			ray.refraction, mat.refraction);
	if (ray.refraction == mat.refraction)
		ray.refraction = AIR_REFRACTION;
	else
		refracted_ray.refraction = mat.refraction;
	new_inter = intersect_scene(refracted_ray, state);
	return (phong_illumination(state, new_inter, refracted_ray));
}
