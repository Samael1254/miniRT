/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_mesh_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:30:40 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_bvh_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_obj_parser_bonus.h"
#include "minirt_parsing_bonus.h"
#include <stdlib.h>

static void	transform_mesh(t_mesh *mesh, t_vec3 pos, t_vec3 rot, double scale)
{
	int	i;

	i = 0;
	rot.x = ft_deg_to_rad(rot.x);
	rot.y = ft_deg_to_rad(rot.y);
	rot.z = ft_deg_to_rad(rot.z);
	while (i < mesh->n_vertices)
	{
		mesh->vertices[i] = ft_4dto3d_vector(ft_rotate_vec4(
					ft_3dto4d_vector(mesh->vertices[i]), rot));
		mesh->vertices[i] = ft_scale_vec3(scale, mesh->vertices[i]);
		mesh->vertices[i] = ft_add_vec3(pos, mesh->vertices[i]);
		i++;
	}
	i = 0;
	while (i < mesh->n_normals)
	{
		mesh->normals[i] = ft_4dto3d_vector(ft_rotate_vec4(
					ft_3dto4d_vector(mesh->normals[i]), rot));
		i++;
	}
}

void	mesh_params(t_state *state, t_object *obj, char **split,
		bool *has_error)
{
	t_vec3	pos;
	t_vec3	rot;

	obj->object_r = parse_obj_file(split[1], state);
	if (!obj->object_r)
	{
		*has_error = true;
		return ;
	}
	obj->type = MESH;
	obj->index_mat = ft_atoi(split[5]);
	pos = get_vector(split[2], has_error);
	if (*has_error)
		return ;
	rot = get_vector(split[3], has_error);
	if (*has_error)
		return ;
	transform_mesh(obj->object_r, pos, rot, ft_atod(split[4]));
	((t_mesh *)obj->object_r)->bvh = create_bvh((t_mesh *)obj->object_r);
}

t_object	*object_mesh(t_state *state, char **split)
{
	t_object	*obj;
	bool		has_error;

	if (!ft_check_error_line(split, 6))
		error("wrong object definition", "mesh needs 5 parameters", state);
	check_line(state, split + 1, 5);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (ft_free_strtab(split), error("malloc failed", "in object_mesh",
				state), NULL);
	mesh_params(state, obj, split, &has_error);
	if (obj->index_mat > state->len_mats_tab || has_error
		|| !((t_mesh *)obj->object_r)->bvh.root)
	{
		free_mesh((t_mesh *)obj->object_r);
		free(obj);
		ft_free_strtab(split);
		return (error("parsing failure", "mesh", state), NULL);
	}
	return (obj);
}
