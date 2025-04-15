/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_bvh.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_binary_tree.h"
#include "ft_math.h"
#include "ft_memory.h"
#include "minirt_bvh.h"
#include "minirt_defs.h"
#include "minirt_intersections.h"
#include <limits.h>
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

static double	intersect_triangles(t_ray ray, t_bvh_elem *elem,
		const t_vec3 *vertices, t_bvh_tr *triangle_r)
{
	double			cur_distance;
	double			distance_min;
	t_bvh_tr		cur_tr;
	unsigned int	i;

	distance_min = INFINITY;
	i = 0;
	while (i < elem->n_triangles)
	{
		cur_tr = elem->triangles[i++];
		cur_distance = intersect_triangle(ray, cur_tr, vertices);
		if (ft_in_rangef(cur_distance, RAY_REACH_MIN, distance_min))
		{
			distance_min = cur_distance;
			*triangle_r = cur_tr;
		}
	}
	return (distance_min);
}

static double	intersect_node(t_ray ray, t_bntree *node, t_mesh *mesh,
		t_bvh_tr *triangle_r)
{
	double		distance_left;
	double		distance_right;
	t_bvh_tr	triangle_left;
	t_bvh_tr	triangle_right;
	t_bvh_elem	*elem;

	elem = (t_bvh_elem *)node->data;
	if (intersect_aabb(ray, elem->box) == INFINITY)
		return (INFINITY);
	if (elem->triangles)
		return (intersect_triangles(ray, elem, mesh->vertices, triangle_r));
	distance_left = INFINITY;
	distance_right = INFINITY;
	triangle_left.id = -1;
	triangle_right.id = -1;
	if (node->left)
		distance_left = intersect_node(ray, node->left, mesh, &triangle_left);
	if (node->right)
		distance_right = intersect_node(ray, node->right, mesh,
				&triangle_right);
	if (distance_left < distance_right)
		*triangle_r = triangle_left;
	else
		*triangle_r = triangle_right;
	return (fmin(distance_left, distance_right));
}

double	intersect_mesh(t_ray ray, t_mesh *mesh, t_object **triangle_obj)
{
	t_bvh_tr	triangle;
	double		distance;

	triangle.id = UINT_MAX;
	distance = intersect_node(ray, mesh->bvh.root, mesh, &triangle);
	if (triangle.id != UINT_MAX)
	{
		*triangle_obj = object_triangle(triangle, (*triangle_obj)->index_mat,
				mesh);
		if (!*triangle_obj)
			return (NAN);
	}
	return (distance);
}
