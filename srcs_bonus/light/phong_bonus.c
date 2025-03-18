#include "ft_algebra.h"
#include "ft_list.h"
#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// static t_vector3d	get_reflection_dir(t_vector3d light_dir,
// double incidence,
// 		t_vector3d normal)
// {
// 	return (ft_sub_vectors3d(ft_scale_vector3d(2 * incidence, normal),
// 			light_dir));
// }

static t_vector3d	light_direction(t_ray ray, t_point_light light)
{
	t_vector3d	light_dir;

	light_dir = ft_normalize_vector3d(ft_sub_vectors3d(light.pos, ray.origin));
	return (light_dir);
}

t_color	ambiant_color(t_ambiant_light a_light, t_color ka)
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

t_color	specular_color(t_intersection inter, t_vector3d light_dir,
		t_vector3d view_dir, t_state *state)
{
	t_material	material;

	material = state->mats_tab[inter.index_mat];
	return (scale_color(material.ks, material.specularity
			* get_specular_term(inter.normal, light_dir, view_dir, material)));
}

t_color	shade_from_one_light(t_intersection inter, t_vector3d view_dir,
		t_state *state)
{
	t_color			color;
	t_ray			light_ray;
	t_intersection	light_inter;
	t_point_light	light;

	light = *(t_point_light *)state->scene.lights;
	light_ray.origin = inter.point;
	light_ray.direction = light_direction(light_ray, light);
	light_inter = intersect_scene(light_ray, state->scene.objects);
	if (ft_supf(ft_distance3d(light_ray.origin, state->scene.p_light.pos),
			ft_distance3d(light_ray.origin, light_inter.point)))
		return (init_color(0, 0, 0));
	color = diffuse_color(ft_dot_vectors3d(light_ray.direction, inter.normal),
			state->mats_tab[inter.index_mat].kd);
	(void)view_dir;
	// color = add_colors(color, specular_color(inter, light_ray.direction,
	// 			view_dir, state));
	color = add_colors(color, scale_color(light.color, light.brightness));
	return (color);
}

void	print_materials(t_state *state)
{
	unsigned int	i;
	t_material		mat;

	i = 1;
	printf("nb materials: %u\n", state->len_mats_tab);
	while (i < state->len_mats_tab)
	{
		mat = state->mats_tab[i];
		printf("mt ");
		printf("%d,%d,%d ", mat.kd.r, mat.kd.g, mat.kd.b);
		printf("%d,%d,%d ", mat.ks.r, mat.ks.g, mat.ks.b);
		printf("%d,%d,%d ", mat.ka.r, mat.ka.g, mat.ka.b);
		printf(" %f\n", mat.specularity);
		i++;
	}
}

t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray)
{
	t_color	color;

	print_materials(state);
	if (inter.point.x == INFINITY)
		return ((state->mats_tab[inter.index_mat]).kd);
	// color = ambiant_color(state->scene.a_light,
	// 		state->mats_tab[inter.index_mat].kd);
	(void)ray;
	color = shade_from_one_light(inter, ray.direction, state);
	// while (state->scene.lights)
	// {
	// 	color = add_colors(color, shade_from_one_light(inter, ray.direction,
	// 				state));
	// 	state->scene.lights = state->scene.lights->next;
	// }
	return (color);
}
