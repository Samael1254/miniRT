#include "ft_algebra.h"
#include "ft_list.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <threads.h>

static t_vector3d	get_reflection_dir(t_vector3d light_dir, double incidence,
		t_vector3d normal)
{
	return (ft_sub_vectors3d(ft_scale_vector3d(2 * incidence, normal),
			light_dir));
}

static t_color	ambiant_color(t_ambiant_light a_light, t_color ka)
{
	return (scale_color(ka, a_light.brightness));
}

static t_color	diffuse_color(double incidence, t_color kd,
		t_point_light p_light)
{
	return (scale_color(kd, incidence * p_light.brightness));
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
static t_color	specular_color(t_vector3d normal, t_vector3d light_dir,
		t_vector3d view_dir, t_material material)
{
	return (scale_color(material.ks, specular * light.brightness));
}

t_color	phong_illumination(t_scene scene, t_material material)
{
	t_color	color;

	color = scale_color(scene.a_light.color, scene.a_light.brightness);
	while (scene.lights)
	{
		color = add_colors(color, diffuse_color(incidence, material));
		color = add_colors(color, specular_color(normal, light_dir, ray_dir,
					material));
		scene.lights = scene.lights->next;
	}
	return (color);
}
