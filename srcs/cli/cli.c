#include "minirt_cli.h"
#include "minirt_defs.h"
#include <fcntl.h>
#include <pthread.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	process_command(t_cli *cli)
{
	char	*command;
	int		old_cancel_state;

	pthread_mutex_lock(&cli->mutex);
	command = cli->command;
	pthread_mutex_unlock(&cli->mutex);
	if (!command)
		return ;
	if (command[0])
		add_history(command);
	printf("command: %s\n", command);
	pthread_mutex_lock(&cli->mutex);
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	free(cli->command);
	cli->command = NULL;
	pthread_setcancelstate(old_cancel_state, NULL);
	cli->is_new_command = false;
	pthread_mutex_unlock(&cli->mutex);
}

static void	cli_cleanup(void *arg)
{
	t_cli	*cli;

	cli = (t_cli *)arg;
	pthread_mutex_lock(&cli->mutex);
	if (cli->command)
		free(cli->command);
	pthread_mutex_unlock(&cli->mutex);
	rl_clear_history();
}

void	cli(t_cli *cli)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		pthread_mutex_lock(&cli->mutex);
		cli->command = strdup(line);
		cli->is_new_command = true;
		pthread_mutex_unlock(&cli->mutex);
		free(line);
	}
}

void	*start_cli(void *args)
{
	pthread_cleanup_push(cli_cleanup, args);
	cli((t_cli *)args);
	pthread_cleanup_pop(false);
	return (NULL);
}

void	init_cli(t_cli *cli)
{
	cli->command = NULL;
	cli->is_new_command = false;
	pthread_mutex_init(&cli->mutex, NULL);
	pthread_create(&cli->thread, NULL, start_cli, cli);
}
