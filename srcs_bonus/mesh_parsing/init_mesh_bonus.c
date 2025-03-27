#include "ft_memory.h"
#include "get_next_line.h"
#include "minirt_bonus.h"
#include "minirt_obj_parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	count_elements(char *filename, t_mesh *mesh, t_state *state)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		mesh_error("could not open file", filename, state, mesh);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_element(line, "v"))
			mesh->n_vertices++;
		else if (is_element(line, "vn"))
			mesh->n_normals++;
		else if (is_element(line, "vt"))
			mesh->n_uvs++;
		else if (is_element(line, "f"))
			mesh->n_faces++;
		free(line);
	}
	close(fd);
}

static void	free_faces(t_vertex **faces)
{
	int	i;

	i = 0;
	while (faces[i])
		free(faces[i++]);
	free(faces);
}

t_mesh	*init_mesh(char *filename, t_state *state)
{
	t_mesh	*mesh;
	int		i;

	mesh = ft_calloc(1, sizeof(t_mesh));
	if (!mesh)
		error("malloc failed", " in init_mesh", state);
	count_elements(filename, mesh, state);
	mesh->vertices = malloc(mesh->n_vertices * sizeof(t_vector3d));
	mesh->normals = malloc(mesh->n_normals * sizeof(t_vector3d));
	mesh->uvs = malloc(mesh->n_uvs * sizeof(t_vector3d));
	mesh->faces = malloc(mesh->n_faces * sizeof(t_vertex *));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->faces)
		mesh_error("malloc failed", "in init_mesh", state, mesh);
	i = 0;
	while (i < mesh->n_faces)
	{
		mesh->faces[i] = malloc(3 * sizeof(t_vertex));
		if (!mesh->faces[i++])
		{
			free_faces(mesh->faces);
			mesh_error("malloc failed", "in init_mesh", state, mesh);
		}
	}
	return (mesh);
}
