#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_light_bonus.h"
#include <math.h>

t_vec3	get_light_direction(t_ray ray, t_point_light light)
{
	t_vec3	light_dir;

	light_dir = ft_normalize_vec3(ft_sub_vec3(light.pos, ray.origin));
	return (light_dir);
}

double	get_dist_attenuation(t_vec3 point, t_vec3 light_pos)
{
	double			dist_attenuation;
	double			distance;
	const double	a = 0.0008;
	const double	b = 0;
	const double	c = 0;

	distance = ft_distance3d(point, light_pos);
	dist_attenuation = 1 / (a * distance * distance + b * distance + c);
	dist_attenuation = ft_clampf(dist_attenuation, 0, 1);
	return (dist_attenuation);
}

t_vec3	get_reflection_dir(t_vec3 light_dir, t_vec3 normal)
{
	double	incidence;

	light_dir = ft_scale_vec3(-1, light_dir);
	incidence = ft_dot_vec3(light_dir, normal);
	return (ft_sub_vec3(ft_scale_vec3(2 * incidence, normal), light_dir));
}

t_vec3	get_refraction_dir(t_vec3 dir, t_vec3 normal, double n1, double n2)
{
	t_vec3	refraction_dir;
	double	cos1;
	double	cos2;
	double	index_ratio;

	cos1 = ft_dot_vec3(normal, dir);
	index_ratio = n1 / n2;
	cos2 = 1 - pow(index_ratio, 2) * (1 - pow(cos1, 2));
	if (cos2 < 0)
		return (get_reflection_dir(dir, normal));
	cos2 = sqrt(cos2);
	refraction_dir = ft_add_vec3(ft_scale_vec3(index_ratio, dir),
			ft_scale_vec3(-index_ratio * cos1 - cos2, normal));
	return (refraction_dir);
}

double	get_specular_term(t_vec3 light_dir, t_vec3 view_dir, t_vec3 normal,
		t_material material)
{
	double	specular;
	t_vec3	reflection_dir;
	double	rv;

	if (ft_equalf(material.specularity, 0))
		return (0);
	reflection_dir = get_reflection_dir(light_dir, normal);
	rv = ft_dot_vec3(reflection_dir, view_dir);
	rv = ft_clampf(rv, 0, rv);
	specular = pow(rv, 100 * material.specularity);
	specular *= material.specularity;
	return (specular);
}
