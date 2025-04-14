#include "ft_memory.h"
#include "ft_strings.h"
#include "get_next_line.h"
#include "minirt_obj_parser_bonus.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	parse_line(char *line, int count[4], t_mesh *mesh)
{
	if (is_element(line, "v"))
	{
		mesh->vertices[count[0]] = parse_vertex(line);
		if (mesh->vertices[count[0]++].x == INFINITY)
			return (false);
	}
	else if (is_element(line, "vn"))
	{
		mesh->normals[count[1]] = parse_vertex(line);
		if (mesh->normals[count[1]++].x == INFINITY)
			return (false);
	}
	else if (is_element(line, "vt"))
	{
		mesh->uvs[count[2]] = parse_uv(line);
		if (mesh->uvs[count[2]++].x == INFINITY)
			return (false);
	}
	else if (is_element(line, "f"))
	{
		mesh->faces[count[3]] = parse_face(line);
		if (!mesh->faces[count[3]++])
			return (false);
	}
	return (true);
}

t_mesh	*parse_obj_file(char *filename, t_state *state)
{
	int		fd;
	char	*line;
	char	*newline;
	int		count[4];
	t_mesh	*mesh;

	mesh = init_mesh(filename, state);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		mesh_error("could not open file", filename, state, mesh);
	ft_bzero(count, 4 * sizeof(int));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (!parse_line(line, count, mesh))
			return (free(line), free_mesh(mesh), NULL);
		free(line);
	}
	close(fd);
	return (mesh);
}
