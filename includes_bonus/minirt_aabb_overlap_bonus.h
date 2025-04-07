#ifndef MINIRT_AABB_OVERLAP_BONUS_H
# define MINIRT_AABB_OVERLAP_BONUS_H

# include "ft_algebra.h"
# include <stdbool.h>

bool	axis1(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis2(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis3(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis4(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis5(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis6(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis7(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis8(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);
bool	axis9(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
			t_vec3 extent);

#endif
