#include "ft_algebra.h"
#include "ft_list.h"
#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>

static t_vector3d	get_reflection_dir(t_vector3d light_dir, t_vector3d normal)
{
	double	incidence;

	light_dir = ft_scale_vector3d(-1, light_dir);
	incidence = ft_dot_vectors3d(light_dir, normal);
	return (ft_sub_vectors3d(ft_scale_vector3d(2 * incidence, normal),
			light_dir));
}

static t_vector3d	light_direction(t_ray ray, t_point_light light)
{
	t_vector3d	light_dir;

	light_dir = ft_normalize_vector3d(ft_sub_vectors3d(light.pos, ray.origin));
	return (light_dir);
}

t_color	ambiant_color(t_ambiant_light a_light, t_material material,
		t_intersection inter)
{
	t_color	color;

	if (material.img_texture.img)
		color = get_pixel_color(material.img_texture, inter.uv);
	else
		color = material.ka;
	return (scale_color(color, a_light.brightness));
}

static t_color	diffuse_color(double incidence, t_material material,
		t_intersection inter)
{
	t_color	color;

	if (material.img_texture.img)
		color = get_pixel_color(material.img_texture, inter.uv);
	else
		color = material.kd;
	incidence = ft_clampf(incidence, 0, 1);
	return (scale_color(color, incidence));
}

static double	get_specular_term(t_vector3d light_dir, t_vector3d view_dir,
		t_vector3d normal, t_material material)
{
	double		specular;
	t_vector3d	reflection_dir;
	double		rv;

	if (ft_equalf(material.specularity, 0))
		return (0);
	reflection_dir = get_reflection_dir(light_dir, normal);
	rv = ft_dot_vectors3d(reflection_dir, view_dir);
	rv = ft_clampf(rv, 0, rv);
	specular = pow(rv, 100 * material.specularity);
	specular *= material.specularity;
	// specular *= (material.specularity + 2) / 8.0;
	return (specular);
}

// static double	get_specular_term(t_vector3d light_dir, t_vector3d view_dir,
// 		t_vector3d normal, t_material material)
// {
// 	double		specular;
// 	t_vector3d	h;
// 	t_vector3d	lpv;
//
// 	if (ft_equalf(material.specularity, 0))
// 		return (0);
// 	lpv = ft_add_vectors3d(light_dir, view_dir);
// 	h = ft_scale_vector3d(1 / ft_vector3d_norm(lpv), lpv);
// 	specular = pow(ft_dot_vectors3d(normal, h), 500);
// 	return (specular);
// }

t_color	specular_color(t_intersection inter, t_vector3d light_dir,
		t_vector3d view_dir, t_state *state)
{
	t_material	material;

	material = state->mats_tab[inter.index_mat];
	return (scale_color(material.ks, get_specular_term(light_dir, view_dir,
				inter.normal, material)));
}

static double	get_dist_attenuation(t_vector3d point, t_vector3d light_pos)
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

t_color	shade_from_one_light(t_intersection inter, t_vector3d view_dir,
		t_state *state, t_point_light light)
{
	t_color			color;
	t_ray			light_ray;
	t_intersection	light_inter;

	light_ray.origin = inter.point;
	light_ray.direction = light_direction(light_ray, light);
	light_inter = intersect_scene(light_ray, state);
	if (ft_supf(ft_distance3d(light_ray.origin, light.pos),
			ft_distance3d(light_ray.origin, light_inter.point)))
		return (init_color(0, 0, 0));
	color = diffuse_color(ft_dot_vectors3d(light_ray.direction, inter.normal),
			state->mats_tab[inter.index_mat], inter);
	color = add_colors(color, specular_color(inter, light_ray.direction,
				view_dir, state));
	color = absorb_colors(color, scale_color(light.color, light.brightness
				* get_dist_attenuation(inter.point, light.pos)));
	return (color);
}

t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray)
{
	t_color	color;
	t_list	*iter;

	if (inter.point.x == INFINITY)
		return (get_sky_color(ray));
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
