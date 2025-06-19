#include "ft_strings.h"
#include "minirt_cli.h"
#include <stdio.h>
#include <string.h>

void	parse_command(char *line)
{
	char	**command;

	command = ft_split(line, ' ');
	if (!command)
		return ;
	if (strcmp(command[0], "keys") == 0)
		keys_cmd();
	else
		printf("Command not found\n");
}
