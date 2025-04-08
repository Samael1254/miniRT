#include "ft_algebra.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <stdlib.h>

static t_vec3	triangle_center(t_vec3 vertices[3])
{
	t_vec3	center;

	center.x = (vertices[0].x + vertices[1].x + vertices[2].x);
	center.y = (vertices[0].y + vertices[1].y + vertices[2].y);
	center.z = (vertices[0].z + vertices[1].z + vertices[2].z);
	return (ft_scale_vec3(1 / 3., center));
}

t_bvh_tr	get_bvh_triangle(const t_vec3 *vertices, t_vertex *face, int index)
{
	int			j;
	t_vec3		tr_vertices[3];
	t_bvh_tr	triangle;

	j = 0;
	while (j < 3)
	{
		triangle.vertices_id[j] = face[j].geo_id - 1;
		tr_vertices[j] = vertices[face[j].geo_id - 1];
		j++;
	}
	triangle.id = index;
	triangle.centroid = triangle_center(tr_vertices);
	return (triangle);
}

static unsigned int	count_triangles_in_aabb(t_bvh_tr *triangles,
		unsigned int n_triangles, t_aabb box)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (i < n_triangles)
	{
		if (is_point_in_aabb(triangles[i++].centroid, box))
			count++;
	}
	return (count);
}

void	get_triangles_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem,
		const t_vec3 *vertices)
{
	unsigned int	i;
	unsigned int	j;

	(void)vertices;
	sub_elem->n_triangles = count_triangles_in_aabb(parent_elem->triangles,
			parent_elem->n_triangles, sub_elem->box);
	sub_elem->triangles = malloc(sub_elem->n_triangles * sizeof(t_bvh_tr));
	if (!sub_elem->triangles || sub_elem->n_triangles == 0)
		return ;
	i = 0;
	j = 0;
	while (i < parent_elem->n_triangles)
	{
		if (is_point_in_aabb(parent_elem->triangles[i].centroid, sub_elem->box))
			sub_elem->triangles[j++] = parent_elem->triangles[i];
		i++;
	}
}
