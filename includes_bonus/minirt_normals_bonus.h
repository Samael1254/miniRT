#ifndef MINIRT_NORMALS_BONUS_H
# define MINIRT_NORMALS_BONUS_H

# include "minirt_defs_bonus.h"

// Object normal

t_vec3	sphere_normal(t_sphere sphere, t_vec3 point);
t_vec3	plane_normal(t_plane plane);
t_vec3	cone_normal(t_cone cone, t_vec3 point);
t_vec3	triangle_normal(t_triangle triangle, t_vec3 point);
t_vec3	cylinder_normal(t_cylinder cylinder, t_vec3 point);

#endif
