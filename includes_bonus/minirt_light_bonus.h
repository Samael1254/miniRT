#ifndef MINIRT_LIGHT_BONUS_H
# define MINIRT_LIGHT_BONUS_H

# include "minirt_defs_bonus.h"

// light_bonus.c
t_vec3	get_reflection_dir(t_vec3 light_dir, t_vec3 normal);
t_color	ambiant_color(t_ambiant_light a_light, t_material material,
		t_intersection inter);
double	get_dist_attenuation(t_vec3 point, t_vec3 light_pos);
t_color	phong_illumination(t_state *state, t_intersection inter, t_ray ray);
t_color	shade_from_one_light(t_intersection inter, t_vec3 view_dir,
		t_state *state, t_point_light light);

#endif // !MINIRT_LIGHT_BONUS_H
