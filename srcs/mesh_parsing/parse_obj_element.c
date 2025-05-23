/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_element.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt_errors.h"
#include "minirt_obj_parser.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

t_vec3	parse_vertex(char *line)
{
	t_vec3	new_vertex;
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (ft_strtab_size(line_data) != 4)
	{
		ft_free_strtab(line_data);
		warning("mesh parsing",
			"wrong number of vertex parameters (must be 3)");
		return (ft_init_vec3(INFINITY));
	}
	new_vertex.x = ft_atod(line_data[1]);
	new_vertex.y = ft_atod(line_data[2]);
	new_vertex.z = ft_atod(line_data[3]);
	ft_free_strtab(line_data);
	return (new_vertex);
}

t_vec2	parse_uv(char *line)
{
	t_vec2	new_vertex;
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (ft_strtab_size(line_data) != 3)
	{
		ft_free_strtab(line_data);
		warning("mesh parsing",
			"wrong number of vertex parameters (must be 3)");
		return (ft_init_vec2(INFINITY));
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

t_vertex	*parse_face(char *line)
{
	t_vertex	*new_face;
	char		**line_data;
	int			i;

	line_data = ft_split(line, ' ');
	if (ft_strtab_size(line_data) != 4)
		return (ft_free_strtab(line_data), warning("mesh parsing",
				"wrong number of vertex parameters (must be 3)"), NULL);
	new_face = malloc(3 * sizeof(t_vertex));
	if (!new_face)
		return (ft_free_strtab(line_data), warning("malloc failed",
				"parse_face"), NULL);
	i = 0;
	while (i < 3)
	{
		new_face[i] = parse_face_vertex(line_data[i + 1]);
		i++;
	}
	ft_free_strtab(line_data);
	return (new_face);
}
