#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "minirt_defs_bonus.h"
# include <stdbool.h>

void		init_mesh(char *filename, t_mesh *mesh);
bool		is_element(char *line, const char *elem);

t_mesh		parse_obj_file(char *filename);
t_vertex	*parse_face(char *line, t_mesh *mesh);
t_vector3d	parse_vertex(char *line, t_mesh *mesh);

void		print_mesh(t_mesh *mesh);

#endif
