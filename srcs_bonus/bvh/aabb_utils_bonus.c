#include "ft_algebra.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>

bool	is_point_in_aabb(t_vec3 point, t_aabb box)
{
	if (point.x < box.min.x || point.x > box.max.x)
		return (false);
	if (point.y < box.min.y || point.y > box.max.y)
		return (false);
	if (point.z < box.min.z || point.z > box.max.z)
		return (false);
	return (true);
}

t_aabb	create_aabb(t_vec3 *vertices, unsigned int n_vertices)
{
	unsigned int	i;
	t_aabb			aabb;

	i = 0;
	aabb.min = ft_init_vec3(INFINITY);
	aabb.max = ft_init_vec3(-INFINITY);
	while (i < n_vertices)
	{
		if (aabb.min.x > vertices[i].x)
			aabb.min.x = vertices[i].x;
		if (aabb.min.y > vertices[i].y)
			aabb.min.y = vertices[i].y;
		if (aabb.min.z > vertices[i].z)
			aabb.min.z = vertices[i].z;
		if (aabb.max.x < vertices[i].x)
			aabb.max.x = vertices[i].x;
		if (aabb.max.y < vertices[i].y)
			aabb.max.y = vertices[i].y;
		if (aabb.max.z < vertices[i].z)
			aabb.max.z = vertices[i].z;
		i++;
	}
	return (aabb);
}

// int	compare_aabb(void *a, void *b)
// {
// 	t_aabb	*a_tmp;
// 	t_aabb	*b_tmp;
// 	float	center_a;
// 	float	center_b;
//
// 	a_tmp = (t_aabb *)a;
// 	b_tmp = (t_aabb *)b;
// 	center_a = (a_tmp->min.x + a_tmp->max.x) / 2;
// 	center_b = (b_tmp->min.x + b_tmp->max.x) / 2;
// 	if (center_a < center_b)
// 		return (-1);
// 	else if (center_a > center_b)
// 		return (1);
// 	return (0);
// }

void	split_aabb(t_aabb box, t_aabb new[2])
{
	t_axis	axis;
	t_vec3	size;
	double	new_pos;
	double	min[3];
	double	max[3];

	size.x = box.max.x - box.min.x;
	size.y = box.max.y - box.min.y;
	size.z = box.max.z - box.min.z;
	axis = X_AXIS;
	if (size.y > size.x && size.y > size.z)
		axis = Y_AXIS;
	else if (size.z > size.y && size.z > size.x)
		axis = Z_AXIS;
	ft_vec3_to_array(box.min, min);
	ft_vec3_to_array(box.max, max);
	new_pos = (max[axis] + min[axis]) / 2;
	min[axis] = new_pos;
	max[axis] = new_pos;
	new[0].min = box.min;
	new[0].max = ft_array_to_vec3(max);
	new[1].min = ft_array_to_vec3(min);
	new[1].max = box.max;
}
