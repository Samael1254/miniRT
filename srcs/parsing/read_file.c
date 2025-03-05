#include "minirt.h"
#include "get_next_line.h"
#include "fcntl.h"

static int	get_data_line(t_state *state, char *line)
{
	char	**split;

	if (!*line)
		return (-1);
	// split on whitespaces
	retrieve_data(state, split);
}

void	read_file(t_state *state, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_program(state, errno); // FIXME: ERRNO?
	line = get_next_line(fd);
	while (line)
	{
		if (get_data_line(state, line) == -1)
		{
			exit_program(state, errno); // FIXME: ERRNO? and free the GNL?
		}
		line = get_next_line(fd);
	}
}
