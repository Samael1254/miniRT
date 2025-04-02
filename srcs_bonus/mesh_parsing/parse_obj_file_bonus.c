#include "ft_memory.h"
#include "ft_strings.h"
#include "get_next_line.h"
#include "minirt_obj_parser.h"
#include "minirt_bvh_bonus.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	parse_line(char *line, int count[4], t_mesh *mesh, t_state *state)
{
	if (is_element(line, "v"))
		mesh->vertices[count[0]++] = parse_vertex(line, mesh, state);
	else if (is_element(line, "vn"))
		mesh->normals[count[1]++] = parse_vertex(line, mesh, state);
	else if (is_element(line, "vt"))
		mesh->uvs[count[2]++] = parse_uv(line, mesh, state);
	else if (is_element(line, "f"))
		mesh->faces[count[3]++] = parse_face(line, mesh, state);
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
		parse_line(line, count, mesh, state);
		free(line);
	}
	close(fd);
	create_aabb(mesh);
	return (mesh);
}
