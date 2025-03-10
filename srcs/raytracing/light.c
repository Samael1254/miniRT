#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <stdbool.h>

static t_vector3d	light_direction(t_ray ray, t_point_light light)
{
	t_vector3d	light_dir;

	light_dir = ft_normalize_vector3d(ft_sub_vectors3d(light.pos, ray.origin));
	return (light_dir);
}

static t_color	apply_brightness(t_color color, double brightness, double angle)
{
	t_color	lit_color;

	// angle = 1;
	lit_color.r = (unsigned char)(color.r * brightness * angle);
	lit_color.g = (unsigned char)(color.g * brightness * angle);
	lit_color.b = (unsigned char)(color.b * brightness * angle);
	return (lit_color);
}

static t_color	shade_material(t_intersection inter, double brightness,
		t_color light_color, t_vector3d light_dir)
{
	t_color	lit_color;

	lit_color = apply_brightness(inter.color, brightness,
			ft_dot_vectors3d(light_dir, inter.normal));
	lit_color = average_colors(lit_color, light_color);
	return (lit_color);
}

t_color	shade_ray(t_intersection inter, t_scene *scene)
{
	t_ray			light_ray;
	t_intersection	light_inter;
	bool			in_shadow;

	light_ray.origin = inter.point;
	light_ray.direction = light_direction(light_ray, scene->p_light);
	light_inter = intersect_scene(light_ray, scene->objects);
	in_shadow = ft_distance3d(light_ray.origin,
			scene->p_light.pos) >= ft_distance3d(light_ray.origin,
			light_inter.point);
	if (in_shadow)
		return (shade_material(inter, scene->a_light.brightness,
				scene->a_light.color, light_ray.direction));
	return (shade_material(inter, ft_maxf(scene->p_light.brightness,
				scene->a_light.brightness), scene->p_light.color,
			light_ray.direction));
}
