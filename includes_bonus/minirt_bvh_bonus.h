#ifndef MINIRT_BVH_BONUS_H
# define MINIRT_BVH_BONUS_H

# include "minirt_defs_bonus.h"
# include <stdbool.h>

t_ivec2	hit_box(bool hit, bool print);
t_aabb	create_aabb(t_mesh *mesh);
double	intersect_aabb(t_ray ray, t_aabb box);

void	ft_vec3_to_array(t_vec3 v, double a[3]);
t_vec3	ft_array_to_vec3(const double a[3]);

// to delete
void	print_aabb(t_aabb aabb);

#endif // !MINIRT_BVH_BONUS_H
