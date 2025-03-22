#include "ft_memory.h"
#include "get_next_line.h"
#include "minirt.h"
#include "minirt_obj_parser.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static void	count_elements(char *filename, int count[4], t_mesh *mesh)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("could not open file", filename, mesh);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_element(line, "v"))
			count[0]++;
		else if (is_element(line, "vn"))
			count[1]++;
		else if (is_element(line, "vt"))
			count[2]++;
		else if (is_element(line, "f"))
			count[3]++;
		free(line);
	}
	close(fd);
}
static void	set_to_null(t_mesh *mesh)
{
	mesh->n_vertices = 0;
	mesh->vertices = NULL;
	mesh->n_normals = 0;
	mesh->normals = NULL;
	mesh->n_uvs = 0;
	mesh->uvs = NULL;
	mesh->n_faces = 0;
	mesh->faces = NULL;
}

static void	free_faces(t_vertex **faces)
{
	int	i;

	i = 0;
	while (faces[i])
		free(faces[i++]);
	free(faces);
}

void	init_mesh(char *filename, t_mesh *mesh)
{
	int	count[4];
	int	i;

	set_to_null(mesh);
	ft_bzero(count, 4 * sizeof(int));
	count_elements(filename, count, mesh);
	mesh->n_vertices = count[0];
	mesh->vertices = malloc(count[0] * sizeof(t_vector3d));
	mesh->n_normals = count[1];
	mesh->normals = malloc(count[1] * sizeof(t_vector3d));
	mesh->n_uvs = count[2];
	mesh->uvs = malloc(count[2] * sizeof(t_vector3d));
	mesh->n_faces = count[3];
	mesh->faces = malloc(count[3] * sizeof(t_vertex *));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->faces)
		error("malloc failed", "in init_mesh", mesh);
	i = 0;
	while (i < mesh->n_faces)
	{
		mesh->faces[i] = malloc(3 * sizeof(t_vertex));
		if (!mesh->faces[i++])
			free_faces(mesh->faces);
	}
}
