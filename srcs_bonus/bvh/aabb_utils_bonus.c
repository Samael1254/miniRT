#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

bool	is_point_in_aabb(t_vec3 point, t_aabb box)
{
	return (ft_in_rangef(point.x, box.min.x, box.max.x) && ft_in_rangef(point.y,
			box.min.y, box.max.y) && ft_in_rangef(point.z, box.min.z,
			box.max.z));
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

int	compare_aabb(void *a, void *b)
{
	t_aabb	*a_tmp;
	t_aabb	*b_tmp;
	float	center_a;
	float	center_b;

	a_tmp = (t_aabb *)a;
	b_tmp = (t_aabb *)b;
	center_a = (a_tmp->min.x + a_tmp->max.x) / 2;
	center_b = (b_tmp->min.x + b_tmp->max.x) / 2;
	if (center_a < center_b)
		return (-1);
	else if (center_a > center_b)
		return (1);
	return (0);
}

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
	new_pos = (box.max.x + box.min.x) / 2;
	ft_vec3_to_array(box.min, min);
	ft_vec3_to_array(box.max, max);
	min[axis] = new_pos;
	new[0].min = ft_array_to_vec3(min);
	max[axis] = new_pos;
	new[1].max = ft_array_to_vec3(max);
}

void	get_triangles_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	sub_elem->n_triangles = count_triangles_in_aabb(parent_elem->triangles,
			parent_elem->n_triangles, sub_elem->box);
	sub_elem->triangles = malloc(sub_elem->n_triangles * sizeof(t_bvh_tr));
	if (!sub_elem->triangles)
		return ;
	while (i < parent_elem->n_triangles)
	{
		if (is_point_in_aabb(parent_elem->triangles[i].center, sub_elem->box))
			sub_elem->triangles[j++] = parent_elem->triangles[i];
		i++;
	}
}
