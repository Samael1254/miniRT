#ifndef MINIRT_LIGHT_BONUS_H
# define MINIRT_LIGHT_BONUS_H

# include "minirt_defs_bonus.h"

// light_bonus.c
t_vec3	get_light_direction(t_ray ray, t_point_light light);
t_vec3	get_reflection_dir(t_vec3 light_dir, t_vec3 normal);
t_vec3	get_refraction_dir(t_vec3 dir, t_vec3 normal, double refraction);
double	get_specular_term(t_vec3 light_dir, t_vec3 view_dir, t_vec3 normal,
			t_material material);
double	get_dist_attenuation(t_vec3 point, t_vec3 light_pos);
t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray);

#endif // !MINIRT_LIGHT_BONUS_H
