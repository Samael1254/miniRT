/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chars.h"
#include "ft_strings.h"
#include "get_next_line.h"
#include "minirt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	append_to_idlist(t_state *state, char **split, int *i)
{
	if (*i >= 3)
	{
		ft_free_strtab(split);
		error("parsing", "you must have only one A, one C, one L!", state);
	}
	state->id_list[*i] = ft_strdup(split[0]);
	if (!state->id_list[*i])
	{
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	*i += 1;
}

static int	get_data_line(t_state *state, char *line, int *i)
{
	char	**split;

	if (!*line)
		return (-1);
	split = ft_split_charset(line, " \t");
	free(line);
	if (!split)
		error("split", "an error as occured", state);
	if (!ft_strncmp(split[0], "#", 1))
		return (ft_free_strtab(split), 0);
	if (insert_in_struct(state, split) == 2)
		append_to_idlist(state, split, i);
	ft_free_strtab(split);
	return (0);
}

static bool	check_line_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !(line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != '+' && line[i] != '-'
			&& line[i] != '.' && line[i] != ',' && line[i] != ' '
			&& line[i] != '\t')
			break ;
		i++;
	}
	if (line[i] != '\0' && line[i + 1] != '\0')
		return (false);
	return (true);
}

static void	check_directory(t_state *state, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY);
	if (fd == -1)
	{
		if (errno == EISDIR)
			error("wrong filename", "given name is a directory", state);
		else if (errno == EACCES)
			error("wrong filename", "can't access due to permission", state);
		error("wrong filename", "cannot open file", state);
	}
	close(fd);
}

void	init_scene(t_state *state, char *filename)
{
	char	*line;
	int		fd;
	int		i;

	check_directory(state, filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("wrong filename", "cannot open file", state);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!check_line_chars(line))
		{
			free(line);
			error("file", "forbidden characters", state);
		}
		if (get_data_line(state, line, &i) == -1)
			error("get_data_line", "an error as occured", state);
		line = get_next_line(fd);
	}
	if (i != 3)
		error("parsing", "one or more major elements missing: A, C, or L",
			state);
}
