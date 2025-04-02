#include "ft_math.h"
#include "ft_memory.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_intersections_bonus.h"
#include <math.h>
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

static t_object	*object_triangle(t_triangle *triangle, unsigned int index_mat)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = TRIANGLE;
	obj->object_r = triangle;
	obj->index_mat = index_mat;
	return (obj);
}

static void	check_new_triangle(double *distance_min, t_triangle **closest_tr,
		double cur_distance, t_triangle *cur_tr)
{
	if (ft_in_rangef(cur_distance, RAY_REACH_MIN, *distance_min))
	{
		*distance_min = cur_distance;
		if (*closest_tr)
			free(*closest_tr);
		*closest_tr = cur_tr;
	}
	else
		free(cur_tr);
}

double	intersect_mesh(t_ray ray, t_mesh *mesh, t_object **triangle_obj)
{
	double		cur_distance;
	double		distance_min;
	t_triangle	*cur_tr;
	t_triangle	*closest_tr;
	int			i;

	if (intersect_aabb(ray, mesh->bvh.box) == INFINITY)
		return (INFINITY);
	distance_min = INFINITY;
	closest_tr = NULL;
	i = 0;
	while (i < mesh->n_faces)
	{
		cur_tr = face_to_triangle(*mesh, mesh->faces[i++]);
		if (!cur_tr)
			return (NAN);
		cur_distance = intersect_triangle(ray, *cur_tr);
		check_new_triangle(&distance_min, &closest_tr, cur_distance, cur_tr);
	}
	if (i > 0)
	{
		*triangle_obj = object_triangle(closest_tr, (*triangle_obj)->index_mat);
		if (!*triangle_obj)
			return (NAN);
	}
	return (distance_min);
}
