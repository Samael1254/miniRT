#include "ft_algebra.h"
#include "ft_list.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_light_bonus.h"
#include <math.h>
#include <stdbool.h>

static t_color	specular_color(t_intersection inter, t_vec3 light_dir,
		t_vec3 view_dir, t_state *state)
{
	t_material	material;

	material = state->mats_tab[inter.index_mat];
	return (scale_color(material.ks, get_specular_term(light_dir, view_dir,
				inter.normal, material)));
}

static t_color	ambiant_color(t_ambiant_light a_light, t_material material,
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

static t_color	diffuse_color(double incidence, t_material material,
		t_intersection inter)
{
	t_color	color;

	color = material.kd;
	if (material.img_texture.img)
		color = absorb_colors(color, get_pixel_color(material.img_texture,
					inter.uv));
	incidence = ft_clampf(incidence, 0, 1);
	return (scale_color(color, incidence));
}

static t_color	shade_from_one_light(t_intersection inter, t_vec3 view_dir,
		t_state *state, t_point_light light)
{
	t_color			color;
	t_ray			light_ray;
	t_intersection	light_inter;

	light_ray.origin = inter.point;
	light_ray.direction = get_light_direction(light_ray, light);
	light_inter = intersect_scene(light_ray, state);
	if (ft_supf(ft_distance3d(light_ray.origin, light.pos),
			ft_distance3d(light_ray.origin, light_inter.point)))
		return (init_color(0, 0, 0));
	color = diffuse_color(ft_dot_vec3(light_ray.direction, inter.normal),
			state->mats_tab[inter.index_mat], inter);
	color = add_colors(color, specular_color(inter, light_ray.direction,
				view_dir, state));
	color = absorb_colors(color, scale_color(light.color, light.brightness
				* get_dist_attenuation(inter.point, light.pos)));
	return (color);
}

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

t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray)
{
	t_color	color;
	t_list	*iter;

	if (inter.point.x == INFINITY)
		return (get_sky_color(state->scene.sky, ray));
	color = ambiant_color(state->scene.a_light,
			state->mats_tab[inter.index_mat], inter);
	if (state->mats_tab[inter.index_mat].reflectance > 0)
		return (reflected_ray(ray, inter, state));
	iter = state->scene.lights;
	while (iter)
	{
		color = add_colors(color, shade_from_one_light(inter, ray.direction,
					state, *(t_point_light *)iter->data));
		iter = iter->next;
	}
	return (color);
}
