/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

void	add_object_to_list(t_state *state, char **split)
{
	t_object	*obj;

	obj = NULL;
	if (!ft_strncmp(split[0], "sp", 2))
		obj = object_sphere(state, split);
	if (!ft_strncmp(split[0], "pl", 2))
		obj = object_plane(state, split);
	if (!ft_strncmp(split[0], "cy", 2))
		obj = object_cylinder(state, split);
	if (obj)
		ft_list_push_back(&state->scene.objects, obj);
}
