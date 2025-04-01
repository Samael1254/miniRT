#include "ft_memory.h"
#include "get_next_line.h"
#include "minirt_errors_bonus.h"
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

t_mesh	*init_mesh(char *filename, t_state *state)
{
	t_mesh	*mesh;

	mesh = ft_calloc(1, sizeof(t_mesh));
	if (!mesh)
		error("malloc failed", " in init_mesh", state);
	count_elements(filename, mesh, state);
	mesh->vertices = malloc(mesh->n_vertices * sizeof(t_vec3));
	mesh->normals = malloc(mesh->n_normals * sizeof(t_vec3));
	mesh->uvs = malloc(mesh->n_uvs * sizeof(t_vec2));
	mesh->faces = malloc(mesh->n_faces * sizeof(t_vertex *));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->faces)
		mesh_error("malloc failed", "in init_mesh", state, mesh);
	return (mesh);
}
