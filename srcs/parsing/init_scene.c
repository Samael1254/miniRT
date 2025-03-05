#include "minirt.h"
#include "libft.h"
#include "get_next_line.h"
#include "fcntl.h"

#include "stdio.h"
static int	get_data_line(t_state *state, char *line)
{
	char	**split;

	if (!*line)
		return (-1);
	split = ft_split_charset(line, " \t");
	if (!split)
		fatal_error("split", "an error as occured", state);
	for (int i = 0; split && split[i]; i++)
		printf("split[%d] -> %s\n", i, split[i]);
	// retrieve_data(state, split);
	return (0);
}

void	init_scene(t_state *state, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		fatal_error("open", "can't open map", state);
	line = get_next_line(fd);
	while (line)
	{
		if (get_data_line(state, line) == -1)
			fatal_error("get_data_line", "an error as occured", state);
		line = get_next_line(fd);
	}
}
