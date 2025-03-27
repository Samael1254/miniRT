#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt_obj_parser.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

t_vector3d	parse_vertex(char *line, t_mesh *mesh, t_state *state)
{
	t_vector3d	new_vertex;
	char		**line_data;

	line_data = ft_split(line, ' ');
	if (ft_strtab_size(line_data) != 4)
	{
		ft_free_strtab(line_data);
		mesh_error("mesh parsing",
			"wrong number of vertex parameters (must be 3)", state, mesh);
	}
	new_vertex.x = ft_atod(line_data[1]);
	new_vertex.y = ft_atod(line_data[2]);
	new_vertex.z = ft_atod(line_data[3]);
	ft_free_strtab(line_data);
	return (new_vertex);
}

t_vector2d	parse_uv(char *line, t_mesh *mesh, t_state *state)
{
	t_vector2d	new_vertex;
	char		**line_data;

	line_data = ft_split(line, ' ');
	if (ft_strtab_size(line_data) != 3)
	{
		ft_free_strtab(line_data);
		mesh_error("mesh parsing", "wrong number of uv parameters (must be 2)",
			state, mesh);
	}
	new_vertex.x = ft_atod(line_data[1]);
	new_vertex.y = ft_atod(line_data[2]);
	ft_free_strtab(line_data);
	return (new_vertex);
}

static t_vertex	parse_face_vertex(char *vertex_data)
{
	t_vertex	new_vertex;
	int			nb_len;
	int			data_len;

	new_vertex.text_id = -1;
	new_vertex.norm_id = -1;
	nb_len = ft_strcspn(vertex_data, "/");
	data_len = (int)ft_strlen(vertex_data);
	vertex_data[nb_len] = '\0';
	new_vertex.geo_id = ft_atoi(vertex_data);
	if (nb_len == data_len)
		return (new_vertex);
	vertex_data += nb_len + 1;
	nb_len = ft_strcspn(vertex_data, "/");
	data_len = (int)ft_strlen(vertex_data);
	vertex_data[nb_len] = '\0';
	if (nb_len > 0)
		new_vertex.text_id = ft_atoi(vertex_data);
	if (nb_len == data_len)
		return (new_vertex);
	vertex_data += nb_len + 1;
	new_vertex.norm_id = ft_atoi(vertex_data);
	return (new_vertex);
}

t_vertex	*parse_face(char *line, t_mesh *mesh, t_state *state)
{
	t_vertex	*new_face;
	char		**line_data;
	int			i;

	line_data = ft_split(line, ' ');
	if (ft_strtab_size(line_data) != 4)
	{
		ft_free_strtab(line_data);
		mesh_error("face", "this parser only handles triangle faces", state,
			mesh);
	}
	new_face = malloc(3 * sizeof(t_vertex));
	if (!new_face)
	{
		ft_free_strtab(line_data);
		mesh_error("malloc failed", "parse_face", state, mesh);
	}
	i = 0;
	while (i < 3)
	{
		new_face[i] = parse_face_vertex(line_data[i + 1]);
		i++;
	}
	ft_free_strtab(line_data);
	return (new_face);
}
