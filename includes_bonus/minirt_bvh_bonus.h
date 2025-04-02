#ifndef MINIRT_BVH_BONUS_H
# define MINIRT_BVH_BONUS_H

# include "minirt_defs_bonus.h"

t_aabb	create_aabb(t_mesh *mesh);

// to delete
void	print_aabb(t_aabb aabb);

#endif // !MINIRT_BVH_BONUS_H
