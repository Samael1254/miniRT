#include "ft_algebra.h"
#include "ft_binary_tree.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static t_bvh_elem	*create_sub_elem(t_bvh_elem *parent_elem, t_aabb sub_box,
		const t_vec3 *vertices)
{
	t_bvh_elem	*sub_elem;

	sub_elem = ft_calloc(1, sizeof(t_bvh_elem));
	if (!sub_elem)
		return (NULL);
	sub_elem->box = sub_box;
	get_triangles_in_aabb(parent_elem, sub_elem);
	if (!sub_elem->triangles)
		return (free(sub_elem), NULL);
	// (void)vertices;
	sub_elem->box = create_aabb(vertices, sub_elem);
	return (sub_elem);
}

static bool	create_sub_elems(t_bvh_elem *sub_elems[2], t_aabb sub_boxes[2],
		t_bvh_elem *parent_elem, const t_vec3 *vertices)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		sub_elems[i] = create_sub_elem(parent_elem, sub_boxes[i], vertices);
		if (!sub_elems[i++])
		{
			free_bvh_elem(sub_elems[0]);
			return (false);
		}
	}
	return (true);
}

static t_bntree	*create_bvh_node(t_bvh_elem *parent_elem, unsigned int depth,
		const t_vec3 *vertices)
{
	t_bntree	*node;
	t_aabb		sub_boxes[2];
	t_bvh_elem	*sub_elems[2];

	node = ft_bntree_create_node(parent_elem);
	if (!node)
		return (free_bvh_elem(parent_elem), NULL);
	// printf("depth: %u\n", depth);
	if (depth == BVH_DEPTH)
		return (node);
	split_aabb(parent_elem->box, sub_boxes);
	if (!create_sub_elems(sub_elems, sub_boxes, parent_elem, vertices))
		return (NULL);
	if (!isinf(sub_elems[0]->box.min.x))
	{
		node->left = create_bvh_node(sub_elems[0], depth + 1, vertices);
		if (!node->left)
			return (free_node(node), NULL);
	}
	if (!isinf(sub_elems[1]->box.min.x))
	{
		node->right = create_bvh_node(sub_elems[1], depth + 1, vertices);
		if (!node->right)
			return (free_node(node->left), free_node(node), NULL);
	}
	free(parent_elem->triangles);
	parent_elem->triangles = NULL;
	return (node);
}

static t_bvh_elem	*init_bvh_elem(t_vec3 *vertices, t_vertex **faces,
		int n_faces)
{
	t_bvh_elem	*data;
	int			i;

	data = ft_calloc(1, sizeof(t_bvh_elem));
	if (!data)
		return (NULL);
	data->n_triangles = n_faces;
	data->triangles = malloc(n_faces * sizeof(t_bvh_tr));
	if (!data->triangles)
		return (free(data), NULL);
	i = 0;
	while (i < n_faces)
	{
		data->triangles[i] = get_bvh_triangle(vertices, faces[i], i);
		i++;
	}
	data->box = create_aabb(vertices, data);
	return (data);
}

t_bvh	create_bvh(t_mesh *mesh)
{
	t_bvh		bvh;
	t_bvh_elem	*root_elem;

	bvh.root = NULL;
	root_elem = init_bvh_elem(mesh->vertices, mesh->faces, mesh->n_faces);
	if (!root_elem)
		return (bvh);
	bvh.root = create_bvh_node(root_elem, 0, mesh->vertices);
	return (bvh);
}
