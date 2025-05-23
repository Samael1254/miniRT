/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_obj_parser.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_OBJ_PARSER_BONUS_H
# define MINIRT_OBJ_PARSER_BONUS_H

# include "minirt_defs.h"
# include <stdbool.h>

t_mesh		*init_mesh(char *filename, t_state *state);

bool		is_element(char *line, const char *elem);
void		free_mesh(t_mesh *mesh);
void		mesh_error(char const *type, char const *msg, t_state *state,
				t_mesh *mesh);

t_mesh		*parse_obj_file(char *filename, t_state *state);
t_vertex	*parse_face(char *line);
t_vec2		parse_uv(char *line);
t_vec3		parse_vertex(char *line);

void		print_mesh(t_mesh *mesh);

#endif
