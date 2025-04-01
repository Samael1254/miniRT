#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
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
	free(mesh);
}

void	mesh_error(char const *type, char const *msg, t_state *state,
		t_mesh *mesh)
{
	free_mesh(mesh);
	error(type, msg, state);
}
