/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_free_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:20:27 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:20:27 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_defs_bonus.h"
#include <stdlib.h>

void	free_triangle_obj(t_object *object)
{
	if (object && object->type == TRIANGLE)
	{
		free(object->object_r);
		free(object);
	}
}

void	free_bvh_elem(void *data)
{
	t_bvh_elem	*elem;

	if (!data)
		return ;
	elem = (t_bvh_elem *)data;
	if (elem->triangles)
		free(elem->triangles);
	free(elem);
}

void	free_node(t_bntree *node)
{
	if (!node)
		return ;
	if (!node->data)
		free_bvh_elem(node->data);
	free(node);
}
