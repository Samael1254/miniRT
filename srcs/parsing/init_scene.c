#include "ft_strings.h"
#include "get_next_line.h"
#include "minirt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_data_line(t_state *state, char *line)
{
	char	**split;

	if (!*line)
		return (-1);
	split = ft_split_charset(line, " \t");
	if (!split)
		error("split", "an error as occured", state);
	insert_in_struct(state, split);
	ft_free_strtab(split);
	return (0);
}
static void	check_directory(t_state *state, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY);
	if (fd == -1)
	{
		if (errno == EISDIR)
			error("wrong filename", "given name is a directory", state);
		error("wrong filename", "cannot open file", state);
	}
	close(fd);
}

void	init_scene(t_state *state, char *filename)
{
	char	*line;
	int		fd;

	check_directory(state, filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error("wrong filename", "cannot open file", state);
	line = get_next_line(fd);
	while (line)
	{
		if (get_data_line(state, line) == -1)
		{
			free(line);
			error("get_data_line", "an error as occured", state);
		}
		free(line);
		line = get_next_line(fd);
	}
	// print_scene(state->scene);
}
