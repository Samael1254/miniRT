#include "ft_binary_tree.h"
#include "ft_math.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_intersections_bonus.h"
#include <math.h>
#include <stddef.h>

double	intersect_triangles(t_ray ray, t_bvh_elem *elem, t_mesh *mesh)
{
	double			cur_distance;
	double			distance_min;
	t_triangle		*cur_tr;
	t_triangle		*closest_tr;
	unsigned int	i;

	distance_min = INFINITY;
	closest_tr = NULL;
	i = 0;
	while (i < elem->n_triangles)
	{
		cur_tr = face_to_triangle(*mesh, mesh->faces[i++]);
		if (!cur_tr)
			return (NAN);
		cur_distance = intersect_triangle(ray, *cur_tr);
		check_new_triangle(&distance_min, &closest_tr, cur_distance, cur_tr);
	}
	if (i > 0)
	{
		*triangle_obj = object_triangle(closest_tr, (*triangle_obj)->index_mat);
		if (!*triangle_obj)
			return (NAN);
	}
	return (distance_min);
}

double	intersect_node(t_ray ray, t_bntree *node, t_mesh *mesh)
{
	double		distance_min;
	double		distance;
	t_bvh_elem	*elem;

	elem = (t_bvh_elem *)node->data;
	if (intersect_aabb(ray, elem->box) == INFINITY)
		return (INFINITY);
	if (elem->triangles)
		return (intersect_triangles(ray, elem, mesh));
	distance_min = intersect_node(ray, node->left, mesh);
	distance = intersect_node(ray, node->right, mesh);
	if (ft_inff(distance, distance_min))
		distance_min = distance;
	return (distance);
}

// double	intersect_bvh(t_ray ray, t_bvh bvh)
// {
// }
