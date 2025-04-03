#include "ft_algebra.h"
#include "ft_binary_tree.h"
#include "ft_math.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

t_vec3	triangle_center(t_vec3 vertices[3])
{
	t_vec3	center;

	center.x = (vertices[0].x + vertices[1].x + vertices[2].x);
	center.y = (vertices[0].y + vertices[1].y + vertices[2].y);
	center.z = (vertices[0].z + vertices[1].z + vertices[2].z);
	return (ft_scale_vec3(1 / 3., center));
}

bool	is_point_in_aabb(t_vec3 point, t_aabb box)
{
	return (ft_in_rangef(point.x, box.min.x, box.max.x) && ft_in_rangef(point.y,
			box.min.y, box.max.y) && ft_in_rangef(point.z, box.min.z,
			box.max.z));
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

t_vec3	*get_triangles_centers(t_vec3 *vertices, t_vertex **faces, int n_faces)
{
	t_vec3	*centers;
	int		i;
	int		j;
	t_vec3	tr_vertices[3];

	centers = malloc(n_faces * sizeof(t_vec3));
	if (!centers)
		return (NULL);
	i = 0;
	while (i < n_faces)
	{
		j = 0;
		while (j < 3)
		{
			tr_vertices[j] = vertices[faces[i][j].geo_id];
			j++;
		}
		centers[i++] = triangle_center(tr_vertices);
	}
	return (centers);
}

t_bvh	create_bvh(t_aabb aabb, t_mesh *mesh)
{
	t_bvh		bvh;
	t_bvh_elem	*data;

	data = ft_calloc(1, sizeof(t_bvh_elem));
	bvh.root = NULL;
	if (!data)
		return (bvh);
	data->box = aabb;
	data->vertices = mesh->vertices;
	data->tr_ids = ;
	data->tr_centers = get_triangles_centers(mesh->vertices, mesh->faces,
			mesh->n_faces);
	bvh.root = ft_bntree_create_node(data);
}
