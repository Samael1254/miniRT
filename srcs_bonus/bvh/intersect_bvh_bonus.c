#include "ft_binary_tree.h"
#include "ft_math.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_intersections_bonus.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static t_triangle	*face_to_triangle(t_mesh mesh, t_vertex *face)
{
	t_triangle	*triangle;
	int			i;

	triangle = malloc(1 * sizeof(t_triangle));
	if (!triangle)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (face[i].geo_id != -1)
			triangle->vertices[i] = mesh.vertices[face[i].geo_id - 1];
		if (face[i].norm_id != -1)
			triangle->normals[i] = mesh.normals[face[i].norm_id - 1];
		if (face[i].text_id != -1)
			triangle->uvs[i] = mesh.uvs[face[i].text_id - 1];
		i++;
	}
	return (triangle);
}

static t_object	*object_triangle(t_bvh_tr triangle, unsigned int index_mat,
		t_mesh *mesh)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = TRIANGLE;
	obj->object_r = face_to_triangle(*mesh, mesh->faces[triangle.id]);
	obj->index_mat = index_mat;
	return (obj);
}

static double	intersect_triangles(t_ray ray, t_bvh_elem *elem, t_mesh *mesh,
		t_object **triangle_obj)
{
	double			cur_distance;
	double			distance_min;
	t_bvh_tr		cur_tr;
	t_bvh_tr		closest_tr;
	unsigned int	i;

	distance_min = INFINITY;
	i = 0;
	while (i < elem->n_triangles)
	{
		cur_tr = elem->triangles[i++];
		cur_distance = intersect_triangle(ray, cur_tr, mesh->vertices);
		if (ft_in_rangef(cur_distance, RAY_REACH_MIN, distance_min))
		{
			distance_min = cur_distance;
			closest_tr = cur_tr;
		}
	}
	if (i > 0 && distance_min < INFINITY)
	{
		*triangle_obj = object_triangle(closest_tr, (*triangle_obj)->index_mat,
				mesh);
		if (!*triangle_obj)
			return (NAN);
	}
	return (distance_min);
}

static double intersect_node(t_ray ray, t_bntree *node, t_mesh *mesh, t_object **triangle_obj)
{
	t_bvh_elem *elem = (t_bvh_elem *)node->data;

	if (intersect_aabb(ray, elem->box) == INFINITY)
		return INFINITY;

	if (elem->triangles)
		return intersect_triangles(ray, elem, mesh, triangle_obj);

	double distance_left = INFINITY;
	double distance_right = INFINITY;
	t_object *left_obj = NULL;
	t_object *right_obj = NULL;

	if (node->left) {
		left_obj = malloc(sizeof(t_object));
		if (!left_obj)
			return NAN;
		left_obj->type = TRIANGLE;
		left_obj->index_mat = (*triangle_obj)->index_mat;
		left_obj->object_r = NULL;
		distance_left = intersect_node(ray, node->left, mesh, &left_obj);
	}

	if (node->right) {
		right_obj = malloc(sizeof(t_object));
		if (!right_obj) {
			if (left_obj)
				free(left_obj);
			return NAN;
		}
		right_obj->type = TRIANGLE;
		right_obj->index_mat = (*triangle_obj)->index_mat;
		right_obj->object_r = NULL;
		distance_right = intersect_node(ray, node->right, mesh, &right_obj);
	}

	if (distance_left < distance_right) {
		if (right_obj)
			free(right_obj);
		*triangle_obj = left_obj;
		return distance_left;
	} else {
		if (left_obj)
			free(left_obj);
		*triangle_obj = right_obj;
		return distance_right;
	}
}

double	intersect_mesh(t_ray ray, t_mesh *mesh, t_object **triangle_obj)
{
	return (intersect_node(ray, mesh->bvh.root, mesh, triangle_obj));
}
