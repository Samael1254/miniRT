/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/15 13:32:14 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_parsing.h"
#include <stdbool.h>
#include <stdlib.h>

static t_sphere	*get_sphere_data(t_state *state, char **split, t_object *obj)
{
	t_sphere	*sp;
	bool		has_error;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
	{
		free(obj);
		ft_free_strtab(split);
		error("malloc failed", "in get_sphere_data", state);
	}
	sp->pos = get_vector(split[1], &has_error);
	sp->diameter = ft_atod(split[2]);
	if (has_error == true)
	{
		free(sp);
		free(obj);
		ft_free_strtab(split);
		error("sphere", "sphere position isn't valid", state);
	}
	return (sp);
}

t_object	*object_sphere(t_state *state, char **split)
{
	t_object	*obj;

	if (!ft_check_error_line(split, 4))
		error("wrong object definition", "sphere needs 4 parameters", state);
	check_line(state, split, 4);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error("malloc failed", "in object_sphere", state);
	}
	obj->object_r = get_sphere_data(state, split, obj);
	obj->type = SPHERE;
	obj->index_mat = ft_atoi(split[3]) - 1;
	if (obj->index_mat > state->len_mats_tab)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error("wrong material index", "sphere", state);
	}
	return (obj);
}
