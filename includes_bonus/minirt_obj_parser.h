#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "ft_algebra.h"
# include <stdbool.h>

typedef struct vertex
{
	int			geo_id;
	int			text_id;
	int			norm_id;
}				t_vertex;

typedef struct s_mesh
{
	t_vector3d	*vertices;
	int			n_vertices;
	t_vector3d	*normals;
	int			n_normals;
	t_vector3d	*uvs;
	int			n_uvs;
	t_vertex	**faces;
	int			n_faces;
}				t_mesh;

void			init_mesh(char *filename, t_mesh *mesh);
bool			is_element(char *line, const char *elem);

t_mesh			parse_obj_file(char *filename);
t_vertex		*parse_face(char *line, t_mesh *mesh);
t_vector3d		parse_vertex(char *line, t_mesh *mesh);

void			print_mesh(t_mesh *mesh);

#endif
