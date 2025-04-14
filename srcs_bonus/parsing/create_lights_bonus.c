/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lights_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
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

static t_point_light	*elem_light(t_state *state, char **split)
{
	t_point_light	*light;
	bool			has_error;

	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
	{
		ft_free_strtab(split);
		error(NULL, "as malloc failed", state);
	}
	light->pos = get_vector(split[1], &has_error);
	light->brightness = ft_atod(split[2]);
	if (light->brightness < 0 || light->brightness > 1 || has_error == true)
	{
		ft_free_strtab(split);
		free(light);
		error("light", "light brightness not in [0-1] or pos error", state);
	}
	light->color = get_color(split[3], &has_error);
	if (has_error == true)
	{
		ft_free_strtab(split);
		free(light);
		error("light", "error of a spot light colors", state);
	}
	return (light);
}

void	add_lights_to_list(t_state *state, char **split)
{
	t_point_light	*light;

	light = elem_light(state, split);
	if (light)
		ft_list_push_back(&state->scene.lights, light);
}
