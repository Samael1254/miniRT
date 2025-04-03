#include "ft_binary_tree.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_bvh_elem	*create_sub_elem(t_bvh_elem *parent_elem, t_aabb sub_box)
{
	t_bvh_elem	*sub_elem;

	sub_elem = ft_calloc(1, sizeof(t_bvh_elem));
	if (!sub_elem)
		return (NULL);
	sub_elem->box = sub_box;
	get_triangles_in_aabb(parent_elem, sub_elem);
	if (!sub_elem->triangles)
		return (free(sub_elem), NULL);
	get_vertices_in_aabb(parent_elem, sub_elem);
	if (!sub_elem->vertices)
		return (free(sub_elem->triangles), free(sub_elem), NULL);
	return (sub_elem);
}

bool	create_sub_elems(t_bvh_elem *sub_elems[2], t_aabb sub_boxes[2],
		t_bvh_elem *parent_elem)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		sub_elems[i] = create_sub_elem(parent_elem, sub_boxes[i]);
		if (!sub_elems[i++])
		{
			free_bvh_elem(sub_elems[0]);
			return (false);
		}
	}
	return (true);
}

t_bntree	*create_bvh_node(t_bvh_elem *parent_elem, unsigned int depth)
{
	t_bntree	*node;
	t_aabb		sub_boxes[2];
	t_bvh_elem	*sub_elems[2];

	node = ft_bntree_create_node(parent_elem);
	if (!node)
		return (free_bvh_elem(parent_elem), NULL);
	if (depth == BVH_DEPTH)
		return (node);
	split_aabb(parent_elem->box, sub_boxes);
	if (!create_sub_elems(sub_elems, sub_boxes, parent_elem))
		return (NULL);
	node->left = create_bvh_node(sub_elems[0], depth + 1);
	if (!node->left)
		return (free_node(node), NULL);
	node->right = create_bvh_node(sub_elems[1], depth + 1);
	if (!node->right)
		return (free_node(node), free_node(node->left), NULL);
	free(parent_elem->triangles);
	free(parent_elem->vertices);
	return (node);
}

t_bvh_elem	*init_bvh_elem(t_aabb box, t_vec3 *vertices, t_vertex **faces,
		int n_faces)
{
	t_bvh_elem	*data;
	int			i;

	data = ft_calloc(1, sizeof(t_bvh_elem));
	if (!data)
		return (NULL);
	data->box = box;
	data->n_triangles = n_faces;
	data->vertices = vertices;
	data->triangles = malloc(n_faces * sizeof(t_bvh_tr));
	if (!data->triangles)
		return (free(data), NULL);
	i = 0;
	while (i < n_faces)
	{
		data->triangles[i] = get_bvh_triangle(vertices, faces[i], i);
		i++;
	}
	return (data);
}

t_bvh	create_bvh(t_aabb aabb, t_mesh *mesh)
{
	t_bvh		bvh;
	t_bvh_elem	*root_elem;

	bvh.root = NULL;
	bvh.depth = BVH_DEPTH;
	root_elem = init_bvh_elem(aabb, mesh->vertices, mesh->faces, mesh->n_faces);
	if (!root_elem)
		return (bvh);
	bvh.root = create_bvh_node(root_elem, 0);
	return (bvh);
}
