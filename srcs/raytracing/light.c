#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>
#include <stdbool.h>

static t_vector3d	light_direction(t_ray ray, t_point_light light)
{
	t_vector3d	light_dir;

	light_dir = ft_normalize_vector3d(ft_sub_vectors3d(light.pos, ray.origin));
	return (light_dir);
}

static t_color	attenuate_color(t_color color, double attenuation)
{
	t_color	lit_color;

	lit_color.r = (unsigned char)(color.r * attenuation);
	lit_color.g = (unsigned char)(color.g * attenuation);
	lit_color.b = (unsigned char)(color.b * attenuation);
	return (lit_color);
}

static double	get_dist_attenuation(t_vector3d point, t_vector3d light_pos)
{
	double			dist_attenuation;
	double			distance;
	const double	a = 0.0001;
	const double	b = 0.1;
	const double	c = 0;

	distance = ft_distance3d(point, light_pos);
	dist_attenuation = 1 / (a * distance * distance + b * distance + c);
	dist_attenuation = ft_clampf(dist_attenuation, 0, 1);
	return (dist_attenuation);
}

static double	get_attenuation(t_intersection inter, bool in_shadow,
		t_vector3d light_dir, t_scene scene)
{
	double	attenuation;
	double	incidence;

	incidence = (ft_dot_vectors3d(light_dir, inter.normal));
	if (in_shadow)
		return (scene.a_light.brightness);
	if (incidence < 0)
		incidence *= -1;
	attenuation = incidence;
	attenuation *= get_dist_attenuation(inter.point, scene.p_light.pos);
	attenuation = ft_lerpf(scene.a_light.brightness, scene.p_light.brightness,
			attenuation);
	if (!ft_in_rangef(attenuation, 0, 1))
		warning("invalid attenuation value", "should be between 0 and 1");
	return (attenuation);
}

static t_color	shade_material(t_color color, double attenuation,
		bool in_shadow, t_scene scene)
{
	t_color	lit_color;

	lit_color = attenuate_color(color, attenuation);
	if (in_shadow)
		lit_color = average_colors(lit_color, scene.a_light.color);
	else
		lit_color = average_colors(lit_color, scene.p_light.color);
	return (lit_color);
}

t_color	shade_ray(t_intersection inter, t_scene *scene)
{
	t_ray			light_ray;
	t_intersection	light_inter;
	bool			in_shadow;
	double			attenuation;

	light_ray.origin = inter.point;
	light_ray.direction = light_direction(light_ray, scene->p_light);
	light_inter = intersect_scene(light_ray, scene->objects);
	in_shadow = ft_distance3d(light_ray.origin,
			scene->p_light.pos) >= ft_distance3d(light_ray.origin,
			light_inter.point);
	attenuation = get_attenuation(inter, in_shadow, light_ray.direction,
			*scene);
	return (shade_material(inter.color, attenuation, in_shadow, *scene));
}
