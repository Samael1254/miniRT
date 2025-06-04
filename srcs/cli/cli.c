#include "minirt_cli.h"
#include "minirt_defs.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static char	*get_command(t_state *state)
{
	char	*line;

	(void)state;
	printf("Enter your command:\n");
	line = readline("> ");
	if (!line)
		return (NULL);
	if (line[0])
		add_history(line);
	return (line);
}

void	cli(t_state *state)
{
	const char	*command;

	(void)state;
	command = get_command(state);
	printf("command: %s\n", command);
}
