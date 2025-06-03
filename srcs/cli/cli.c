#include "minirt_defs.h"
#include <pthread.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	*cli_loop(void *arg)
{
	const char	*line;
	t_cli		*cli;

	cli = (t_cli *)arg;
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		pthread_mutex_lock(&cli->cli_mutex);
		cli->command = strdup(line);
		cli->has_new_command = true;
		pthread_mutex_unlock(&cli->cli_mutex);
	}
	return (NULL);
}
