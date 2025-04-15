/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cone_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/15 13:30:56 by gfulconi         ###   ########.fr       */
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

static t_cone	*get_cone_data(t_state *state, char **split, t_object *obj)
{
	t_cone	*cone;
	bool	has_error;
	double	slope;

	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
	{
		free(obj);
		ft_free_strtab(split);
		error("malloc failed", "in get_cone_data", state);
	}
	slope = ft_atod(split[3]);
	cone->pos = get_vector(split[1], &has_error);
	cone->axis = get_vector(split[2], &has_error);
	if (has_error == true || slope < 1 || slope > 179)
	{
		free(cone);
		free(obj);
		ft_free_strtab(split);
		error("cone", "slope or position isn't valid", state);
	}
	cone->slope = ft_deg_to_rad(slope);
	return (cone);
}

t_object	*object_cone(t_state *state, char **split)
{
	t_object	*obj;

	if (!ft_check_error_line(split, 5))
		error("wrong object definition", "cone needs 4 parameters", state);
	check_line(state, split, 5);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error("malloc failed", "in object_cone", state);
	}
	obj->object_r = get_cone_data(state, split, obj);
	obj->type = CONE;
	obj->index_mat = ft_atoi(split[4]) - 1;
	if (obj->index_mat > state->len_mats_tab)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error("wrong material index", "cone", state);
	}
	return (obj);
}
