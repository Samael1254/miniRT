#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include "minirt_intersections_bonus.h"
#include "minirt_light_bonus.h"
#include <math.h>

static t_vec3	light_direction(t_ray ray, t_point_light light)
{
	t_vec3	light_dir;

	light_dir = ft_normalize_vec3(ft_sub_vec3(light.pos, ray.origin));
	return (light_dir);
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

static double	get_specular_term(t_vec3 light_dir, t_vec3 view_dir,
		t_vec3 normal, t_material material)
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

static t_color	specular_color(t_intersection inter, t_vec3 light_dir,
		t_vec3 view_dir, t_state *state)
{
	t_material	material;

	material = state->mats_tab[inter.index_mat];
	return (scale_color(material.ks, get_specular_term(light_dir, view_dir,
				inter.normal, material)));
}

t_color	shade_from_one_light(t_intersection inter, t_vec3 view_dir,
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
	color = diffuse_color(ft_dot_vec3(light_ray.direction, inter.normal),
			state->mats_tab[inter.index_mat], inter);
	color = add_colors(color, specular_color(inter, light_ray.direction,
				view_dir, state));
	color = absorb_colors(color, scale_color(light.color, light.brightness
				* get_dist_attenuation(inter.point, light.pos)));
	return (color);
}
