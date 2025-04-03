#include <stdlib.h>
#include "ft_memory.h"
#include "minirt_defs_bonus.h"
#include "minirt_bvh_bonus.h"

static t_vec3	triangle_center(t_vec3 vertices[3])
{
	t_vec3	center;

	center.x = (vertices[0].x + vertices[1].x + vertices[2].x);
	center.y = (vertices[0].y + vertices[1].y + vertices[2].y);
	center.z = (vertices[0].z + vertices[1].z + vertices[2].z);
	return (ft_scale_vec3(1 / 3., center));
}

static unsigned int	count_vertices_in_aabb(t_bvh_elem *sub_elem,
		bool *gotten_vertices)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	count;

	count = 0;
	i = 0;
	while (i < sub_elem->n_triangles)
	{
		j = 0;
		while (j < 3)
		{
			if (gotten_vertices[sub_elem->triangles[i].vertices_id[j]] == false)
				count++;
			gotten_vertices[sub_elem->triangles[i].vertices_id[j++]] = true;
		}
		i++;
	}
	return (count);
}

t_bvh_tr	get_bvh_triangle(const t_vec3 *vertices, t_vertex *face, int index)
{
	int			j;
	t_vec3		tr_vertices[3];
	t_bvh_tr	triangle;

	j = 0;
	while (j < 3)
	{
		triangle.vertices_id[j] = face[j].geo_id;
		tr_vertices[j] = vertices[face[j].geo_id];
		j++;
	}
	triangle.center = triangle_center(tr_vertices);
	triangle.id = index;
	return (triangle);
}

unsigned int	count_triangles_in_aabb(t_bvh_tr *triangles,
		unsigned int n_triangles, t_aabb box)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (i < n_triangles)
		if (is_point_in_aabb(triangles[i++].center, box))
			count++;
	return (count);
}

void	get_vertices_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem)
{
	bool			*gotten_vertices;
	unsigned int	i;
	unsigned int	j;

	gotten_vertices = ft_calloc(parent_elem->n_vertices, sizeof(bool));
	if (!gotten_vertices)
		return ;
	sub_elem->n_vertices = count_vertices_in_aabb(sub_elem, gotten_vertices);
	sub_elem->vertices = malloc(sub_elem->n_vertices * sizeof(t_vec3));
	if (!sub_elem->vertices)
		return ;
	i = 0;
	j = 0;
	while (i < parent_elem->n_vertices)
	{
		if (gotten_vertices[i] == true)
			sub_elem->vertices[j++] = parent_elem->vertices[i];
		i++;
	}
}
