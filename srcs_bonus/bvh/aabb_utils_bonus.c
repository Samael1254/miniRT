#include "ft_algebra.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>

bool	is_point_in_aabb(t_vec3 point, t_aabb box)
{
	const double	epsilon = 0;

	if (point.x < box.min.x - epsilon || point.x > box.max.x + epsilon)
		return (false);
	if (point.y < box.min.y - epsilon || point.y > box.max.y + epsilon)
		return (false);
	if (point.z < box.min.z - epsilon || point.z > box.max.z + epsilon)
		return (false);
	return (true);
}

t_aabb	create_aabb(const t_vec3 *vertices, t_bvh_elem *sub_elem)
{
	unsigned int	i;
	unsigned int	j;
	t_aabb			aabb;
	t_vec3			vertex;

	i = 0;
	aabb.min = ft_init_vec3(INFINITY);
	aabb.max = ft_init_vec3(-INFINITY);
	while (i < sub_elem->n_triangles)
	{
		j = 0;
		while (j < 3)
		{
			vertex = vertices[sub_elem->triangles[i].vertices_id[j++]];
			aabb.min.x = fmin(aabb.min.x, vertex.x);
			aabb.min.y = fmin(aabb.min.y, vertex.y);
			aabb.min.z = fmin(aabb.min.z, vertex.z);
			aabb.max.x = fmax(aabb.max.x, vertex.x);
			aabb.max.y = fmax(aabb.max.y, vertex.y);
			aabb.max.z = fmax(aabb.max.z, vertex.z);
		}
		i++;
	}
	return (aabb);
}

void	split_aabb(t_aabb box, t_aabb new[2])
{
	t_axis	axis;
	t_vec3	size;
	double	new_pos;
	double	min[3];
	double	max[3];

	size = ft_sub_vec3(box.max, box.min);
	axis = X_AXIS;
	if (size.y > size.x && size.y > size.z)
		axis = Y_AXIS;
	else if (size.z > size.y && size.z > size.x)
		axis = Z_AXIS;
	ft_vec3_to_array(box.min, min);
	ft_vec3_to_array(box.max, max);
	new_pos = (max[axis] + min[axis]) * 0.5;
	min[axis] = new_pos;
	max[axis] = new_pos;
	new[0].min = box.min;
	new[0].max = ft_array_to_vec3(max);
	new[1].min = ft_array_to_vec3(min);
	new[1].max = box.max;
}
