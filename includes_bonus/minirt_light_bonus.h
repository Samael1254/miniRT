#ifndef MINIRT_LIGHT_BONUS_H
# define MINIRT_LIGHT_BONUS_H

# include "minirt_defs_bonus.h"

t_color	refract_reflect_rays(t_color color, t_ray ray, t_intersection inter,
			t_state *state);
t_color	trace_point_light(t_point_light light, t_ray ray);

// light_bonus.c

t_vec3	get_light_direction(t_ray ray, t_point_light light);
t_vec3	get_reflection_dir(t_vec3 light_dir, t_vec3 normal);
t_vec3	get_refraction_dir(t_vec3 dir, t_vec3 normal, double n1, double n2);
double	get_specular_term(t_vec3 light_dir, t_vec3 view_dir, t_vec3 normal,
			t_material material);
double	get_dist_attenuation(t_vec3 point, t_vec3 light_pos);
t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray);

// shade_from_one_light_utils_bonus.c
t_color	specular_color(t_intersection inter, t_vec3 light_dir, t_vec3 view_dir,
		t_state *state);
t_color	ambiant_color(t_ambiant_light a_light, t_material material,
		t_intersection inter);
t_color	diffuse_color(double incidence, t_material material,
		t_intersection inter);

#endif // !MINIRT_LIGHT_BONUS_H
