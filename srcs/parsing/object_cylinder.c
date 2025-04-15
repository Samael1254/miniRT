/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/15 13:31:44 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt.h"
#include <stdlib.h>

static t_cylinder	*get_cylinder_data(t_state *state, char **sp, t_object *obj)
{
	t_cylinder	*cy;
	bool		has_error;

	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
	{
		free(obj);
		ft_free_strtab(sp);
		error(NULL, "malloc failed", state);
	}
	cy->pos = get_vector(sp[1], &has_error);
	if (!has_error)
		cy->axis = get_vector(sp[2], &has_error);
	if (!is_vec3_in_range(cy->axis, -1, 1) || has_error == true
		|| !is_norm_vector_valid(cy->axis))
	{
		free(obj);
		free(cy);
		ft_free_strtab(sp);
		error("wrong parameter", "cylinder axis should be normalized", state);
	}
	cy->diameter = ft_atod(sp[3]);
	cy->height = ft_atod(sp[4]);
	return (cy);
}

t_object	*object_cylinder(t_state *state, char **split)
{
	t_object	*obj;
	bool		has_error;

	if (!ft_check_error_line(split, 6))
		error("wrong object definition", "cylinder needs 5 parameters", state);
	check_line(state, split, 6);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	obj->object_r = get_cylinder_data(state, split, obj);
	obj->type = CYLINDER;
	obj->color = get_color(split[5], &has_error);
	if (has_error == true)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	return (obj);
}
