#include "ft_memory.h"
#include "ft_strings.h"
#include "get_next_line.h"
#include "minirt.h"
#include "minirt_obj_parser.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	parse_line(char *line, int count[4], t_mesh *mesh)
{
	if (is_element(line, "v"))
		mesh->vertices[count[0]++] = parse_vertex(line, mesh);
	else if (is_element(line, "vn"))
		mesh->normals[count[1]++] = parse_vertex(line, mesh);
	else if (is_element(line, "vt"))
		mesh->uvs[count[2]++] = parse_vertex(line, mesh);
	else if (is_element(line, "f"))
		mesh->faces[count[3]++] = parse_face(line, mesh);
}

t_mesh	parse_obj_file(char *filename)
{
	int		fd;
	char	*line;
	char	*newline;
	int		count[4];
	t_mesh	mesh;

	init_mesh(filename, &mesh);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("could not open file", filename, &mesh);
	ft_bzero(count, 4 * sizeof(int));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		parse_line(line, count, &mesh);
		free(line);
	}
	close(fd);
	return (mesh);
}
