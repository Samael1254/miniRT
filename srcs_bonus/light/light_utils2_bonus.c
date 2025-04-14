#include "minirt_defs_bonus.h"
#include "minirt_light_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_graphics_bonus.h"
#include <math.h>

t_color	trace_point_light(t_point_light light, t_ray ray)
{
	t_color	color;
	double	angle;
	t_vec3	light_dir;

	light_dir = ft_sub_vec3(light.pos, ray.origin);
	angle = ft_dot_vec3(ft_normalize_vec3(light_dir), ray.direction);
	if (angle < 0)
		return (init_color(0, 0, 0));
	color = scale_color(light.color, pow(angle, 1 * pow(ft_vec3_norm(light_dir),
					2)));
	return (color);
}

t_ray	get_shadow_ray(t_intersection inter, t_point_light light)
{
	t_ray	light_ray;

	light_ray.origin = inter.point;
	light_ray.direction = get_light_direction(light_ray, light);
	return (light_ray);
}

t_intersection	get_light_intersection(t_ray shadow_ray, t_state *state)
{
	t_intersection	light_inter;

	light_inter = intersect_scene(shadow_ray, state);
	return (light_inter);
}
