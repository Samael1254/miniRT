#include "ft_algebra.h"
#include "ft_binary_tree.h"
#include "ft_math.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>
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

void	free_bvh_elem(t_bvh_elem *elem)
{
	if (!elem)
		return ;
	if (elem->triangles)
		free(elem->triangles);
	free(elem);
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

unsigned int	count_vertices_in_aabb(t_bvh_elem *sub_elem,
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

void	free_node(t_bntree *node)
{
	if (!node)
		return ;
	if (!node->data)
		free_bvh_elem(node->data);
	free(node);
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
