#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include "minirt_bvh_bonus.h"
#include <math.h>

t_vec3	triangle_center(t_vec3 vertices[3])
{
	t_vec3	center;

	center.x = (vertices[0].x + vertices[1].x + vertices[2].x);
	center.y = (vertices[0].y + vertices[1].y + vertices[2].y);
	center.z = (vertices[0].z + vertices[1].z + vertices[2].z);
	return (ft_scale_vec3(1 / 3., center));
}

t_aabb	create_aabb(t_mesh *mesh)
{
	int		i;
	t_aabb	aabb;

	i = 0;
	aabb.min = ft_init_vec3(INFINITY);
	aabb.max = ft_init_vec3(-INFINITY);
	while (i < mesh->n_vertices)
	{
		if (aabb.min.x > mesh->vertices[i].x)
			aabb.min.x = mesh->vertices[i].x;
		if (aabb.min.y > mesh->vertices[i].y)
			aabb.min.y = mesh->vertices[i].y;
		if (aabb.min.z > mesh->vertices[i].z)
			aabb.min.z = mesh->vertices[i].z;
		if (aabb.max.x < mesh->vertices[i].x)
			aabb.max.x = mesh->vertices[i].x;
		if (aabb.max.y < mesh->vertices[i].y)
			aabb.max.y = mesh->vertices[i].y;
		if (aabb.max.z < mesh->vertices[i].z)
			aabb.max.z = mesh->vertices[i].z;
		i++;
	}
	return (aabb);
}
