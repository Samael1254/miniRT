#include "ft_algebra.h"
#include "ft_list.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_light_bonus.h"
#include <math.h>
#include <stdbool.h>

t_vec3	get_reflection_dir(t_vec3 light_dir, t_vec3 normal)
{
	double	incidence;

	light_dir = ft_scale_vec3(-1, light_dir);
	incidence = ft_dot_vec3(light_dir, normal);
	return (ft_sub_vec3(ft_scale_vec3(2 * incidence, normal), light_dir));
}

t_color	ambiant_color(t_ambiant_light a_light, t_material material,
		t_intersection inter)
{
	t_color	color;

	color = material.ka;
	if (material.img_texture.img)
		color = absorb_colors(color, get_pixel_color(material.img_texture,
					inter.uv));
	else
		color = absorb_colors(color, a_light.color);
	return (scale_color(color, a_light.brightness));
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

t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray)
{
	t_color	color;
	t_list	*iter;

	if (inter.point.x == INFINITY)
		return (get_sky_color(state->scene.sky, ray));
	color = ambiant_color(state->scene.a_light,
			state->mats_tab[inter.index_mat], inter);
	iter = state->scene.lights;
	while (iter)
	{
		color = add_colors(color, shade_from_one_light(inter, ray.direction,
					state, *(t_point_light *)iter->data));
		iter = iter->next;
	}
	return (color);
}
