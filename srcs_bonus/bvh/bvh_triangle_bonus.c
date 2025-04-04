#include "ft_algebra.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <stdio.h>
#include <stdlib.h>

static t_vec3	triangle_center(t_vec3 vertices[3])
{
	t_vec3	center;

	center = ft_add_vec3(vertices[0], ft_add_vec3(vertices[1], vertices[2]));
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
	triangle.center = triangle_center(tr_vertices);
	triangle.id = index;
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
		if (is_point_in_aabb(triangles[i++].center, box))
			count++;
	return (count);
}

void	get_triangles_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem)
{
	unsigned int	i;
	unsigned int	j;

	sub_elem->n_triangles = count_triangles_in_aabb(parent_elem->triangles,
			parent_elem->n_triangles, sub_elem->box);
	printf("n_triangles: %u\n", sub_elem->n_triangles);
	sub_elem->triangles = malloc(sub_elem->n_triangles * sizeof(t_bvh_tr));
	if (!sub_elem->triangles)
		return ;
	i = 0;
	j = 0;
	while (i < parent_elem->n_triangles)
	{
		if (is_point_in_aabb(parent_elem->triangles[i].center, sub_elem->box))
			sub_elem->triangles[j++] = parent_elem->triangles[i];
		i++;
	}
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

void	get_vertices_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem)
{
	bool			*gotten_vertices;
	unsigned int	i;
	unsigned int	j;

	gotten_vertices = ft_calloc(parent_elem->n_vertices, sizeof(bool));
	if (!gotten_vertices)
		return ;
	sub_elem->n_vertices = count_vertices_in_aabb(sub_elem, gotten_vertices);
	printf("n_vertices: %u\n", sub_elem->n_vertices);
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
