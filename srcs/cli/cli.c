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

void	process_command(t_cli *cli)
{
	char	*command;
	int		old_cancel_state;

	pthread_mutex_lock(&cli->mutex);
	command = strdup(cli->command);
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	free(cli->command);
	cli->command = NULL;
	cli->is_new_command = false;
	pthread_setcancelstate(old_cancel_state, NULL);
	if (!command)
	{
		pthread_mutex_unlock(&cli->mutex);
		return ;
	}
	write(STDOUT_FILENO, "command: ", 9);
	write(STDOUT_FILENO, command, strlen(command));
	write(STDOUT_FILENO, "\n", 1);
	free(command);
	pthread_mutex_unlock(&cli->mutex);
}

static void	cli(t_cli *cli)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		pthread_mutex_lock(&cli->mutex);
		cli->command = strdup(line);
		cli->is_new_command = true;
		pthread_mutex_unlock(&cli->mutex);
		free(line);
	}
}

void	*start_cli(void *args)
{
	pthread_mutex_lock(&((t_cli *)args)->mutex);
	pthread_cleanup_push(cli_cleanup, args);
	pthread_mutex_unlock(&((t_cli *)args)->mutex);
	cli((t_cli *)args);
	pthread_mutex_lock(&((t_cli *)args)->mutex);
	pthread_cleanup_pop(false);
	pthread_mutex_unlock(&((t_cli *)args)->mutex);
	return (NULL);
}

void	init_cli(t_cli *cli)
{
	cli->command = NULL;
	cli->is_new_command = false;
	pthread_mutex_init(&cli->mutex, NULL);
	pthread_create(&cli->thread, NULL, start_cli, cli);
	cli->is_init = true;
}
