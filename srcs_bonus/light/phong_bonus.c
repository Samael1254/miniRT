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

static t_color	diffuse_color(double incidence, t_color kd)
{
	return (attenuate_color(kd, incidence));
}

static t_color	specular_color(t_vector3d normal, t_vector3d light_dir,
		t_vector3d ray_dir, t_material material)
{
	double		incidence;
	t_vector3d	reflection_dir;
	double		attenuation;

	incidence = ft_dot_vectors3d(light_dir, normal);
	reflection_dir = get_reflection_dir(light_dir, incidence, normal);
	attenuation = pow(ft_dot_vectors3d(reflection_dir, ray_dir),
			material.specularity);
	return (attenuate_color(material.ks, attenuation));
}

t_color	phong_illumination(t_scene scene)
{
	t_color	color;

	while (scene.lights)
	{
		scene.lights = scene.lights->next;
	}
}
