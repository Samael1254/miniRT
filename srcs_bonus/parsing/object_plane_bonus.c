/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/15 13:32:13 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_parsing_bonus.h"
#include <stdbool.h>
#include <stdlib.h>

static t_plane	*get_plane_data(t_state *state, char **split, t_object *obj)
{
	t_plane	*pl;
	bool	has_error;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
	{
		free(obj);
		ft_free_strtab(split);
		error("malloc failed", "in get_plane_data", state);
	}
	pl->point = get_vector(split[1], &has_error);
	if (!has_error)
		pl->normal = get_vector(split[2], &has_error);
	if (!is_vec3_in_range(pl->normal, -1, 1) || has_error == true
		|| !is_norm_vector_valid(pl->normal))
	{
		free(obj);
		free(pl);
		ft_free_strtab(split);
		error("wrong parameter", "plane normal vector should be normalized",
			state);
	}
	return (pl);
}

t_object	*object_plane(t_state *state, char **split)
{
	t_object	*obj;

	if (!ft_check_error_line(split, 4))
		error("wrong object definition", "plane needs 4 parameters", state);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error("malloc failed", "in object_plane", state);
	}
	obj->object_r = get_plane_data(state, split, obj);
	obj->type = PLANE;
	obj->index_mat = ft_atoi(split[3]) - 1;
	if (obj->index_mat > state->len_mats_tab)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error("wrong material index", "plane", state);
	}
	return (obj);
}
