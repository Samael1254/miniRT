#include "ft_algebra.h"
#include "ft_list.h"
#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>

// static t_vector3d	get_reflection_dir(t_vector3d light_dir,
// double incidence,
// 		t_vector3d normal)
// {
// 	return (ft_sub_vectors3d(ft_scale_vector3d(2 * incidence, normal),
// 			light_dir));
// }

static t_color	ambiant_color(t_ambiant_light a_light, t_color ka)
{
	return (scale_color(ka, a_light.brightness));
}

static t_color	diffuse_color(double incidence, t_color kd)
{
	return (scale_color(kd, incidence));
}

static double	get_specular_term(t_vector3d light_dir, t_vector3d view_dir,
		t_vector3d normal, t_material material)
{
	double		specular;
	t_vector3d	lpv;

	// double		incidence;
	// t_vector3d	reflection_dir;
	// double		attenuation;
	// incidence = ft_dot_vectors3d(light_dir, normal);
	// reflection_dir = get_reflection_dir(light_dir, incidence, normal);
	// attenuation = pow(ft_dot_vectors3d(reflection_dir, view_dir),
	// 		material.specularity);
	lpv = ft_add_vectors3d(light_dir, view_dir);
	specular = pow(ft_dot_vectors3d(ft_scale_vector3d(1 / ft_vector3d_norm(lpv),
					lpv), normal), material.specularity);
	return (specular);
}
static t_color	specular_color(t_intersection inter, t_vector3d light_dir,
		t_vector3d view_dir)
{
	return (scale_color(inter.material.ks, inter.material.specularity
			* get_specular_term(inter.normal, light_dir, view_dir,
				inter.material)));
}

static t_color	shade_from_one_light(t_intersection inter, t_vector3d view_dir,
		t_scene scene)
{
	t_color			color;
	t_ray			light_ray;
	t_intersection	light_inter;
	t_point_light	light;

	light = *(t_point_light *)scene.lights;
	light_ray.origin = inter.point;
	light_ray.direction = light_direction(light_ray, light);
	light_inter = intersect_scene(light_ray, scene.objects);
	if (ft_supf(ft_distance3d(light_ray.origin, scene.p_light.pos),
			ft_distance3d(light_ray.origin, light_inter.point)))
		return (init_color(0, 0, 0));
	color = diffuse_color(ft_dot_vectors3d(light_ray.direction, inter.normal),
			inter.material.kd);
	color = add_colors(color, specular_color(inter, light_ray.direction,
				view_dir));
	color = add_colors(color, scale_color(light.color, light.brightness));
	return (color);
}

t_color	phong_illumination(t_scene scene, t_intersection inter, t_ray ray)
{
	t_color	color;

	if (inter.point.x == INFINITY)
		return (inter.material.kd);
	color = ambiant_color(scene.a_light, inter.material.ka);
	while (scene.lights)
	{
		color = add_colors(color, shade_from_one_light(inter, ray.direction,
					scene));
		scene.lights = scene.lights->next;
	}
	return (color);
}
