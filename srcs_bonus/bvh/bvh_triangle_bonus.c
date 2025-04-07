#include "ft_algebra.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <stdlib.h>

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
	return (triangle);
}

static unsigned int	count_triangles_in_aabb(t_bvh_tr *triangles,
		unsigned int n_triangles, t_aabb box, const t_vec3 *vertices)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (i < n_triangles)
		if (triangle_aabb_overlap(triangles[i++].vertices_id, box, vertices))
			count++;
	return (count);
}

void	get_triangles_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem,
		const t_vec3 *vertices)
{
	unsigned int	i;
	unsigned int	j;

	sub_elem->n_triangles = count_triangles_in_aabb(parent_elem->triangles,
			parent_elem->n_triangles, sub_elem->box, vertices);
	sub_elem->triangles = malloc(sub_elem->n_triangles * sizeof(t_bvh_tr));
	if (!sub_elem->triangles || sub_elem->n_triangles == 0)
		return ;
	i = 0;
	j = 0;
	while (i < parent_elem->n_triangles)
	{
		if (triangle_aabb_overlap(parent_elem->triangles[i].vertices_id,
				sub_elem->box, vertices))
			sub_elem->triangles[j++] = parent_elem->triangles[i];
		i++;
	}
}
