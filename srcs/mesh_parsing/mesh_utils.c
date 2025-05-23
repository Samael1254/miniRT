/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "ft_strings.h"
#include "minirt_bvh.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include <stdbool.h>
#include <stdlib.h>

bool	is_element(char *line, const char *elem)
{
	int	keyword_len;

	keyword_len = ft_strcspn(line, " ");
	if (keyword_len == 0)
		return (false);
	return (ft_strncmp(line, elem, keyword_len) == 0);
}

void	free_mesh(t_mesh *mesh)
{
	int	i;

	if (!mesh)
		return ;
	if (mesh->vertices)
		free(mesh->vertices);
	if (mesh->normals)
		free(mesh->normals);
	if (mesh->uvs)
		free(mesh->uvs);
	i = 0;
	while (i < mesh->n_faces)
		if (mesh->faces[i++])
			free(mesh->faces[i - 1]);
	if (mesh->faces)
		free(mesh->faces);
	if (mesh->bvh.root)
		ft_bntree_clear(mesh->bvh.root, free_bvh_elem);
	free(mesh);
}

void	mesh_error(char const *type, char const *msg, t_state *state,
		t_mesh *mesh)
{
	(void)type;
	(void)msg;
	(void)state;
	free_mesh(mesh);
	error(type, msg, state);
}
