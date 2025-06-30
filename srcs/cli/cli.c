#include "ft_strings.h"
#include "minirt_base.h"
#include "minirt_cli.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
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
	if (pthread_mutex_trylock(&cli->mutex) == 0)
	{
		if (cli->command)
			free(cli->command);
		pthread_mutex_unlock(&cli->mutex);
	}
	rl_clear_history();
}

static enum e_cmd_status	exec_command(char *line, t_state *state)
{
	char				**command;
	enum e_cmd_status	status;

	command = ft_split(line, ' ');
	if (!command || !command[0])
		return (CS_EXIT);
	if (strcmp(command[0], "keys") == 0)
		status = keys_cmd();
	else if (strcmp(command[0], "screenshot") == 0)
		status = screenshot_cmd(state);
	else if (strcmp(command[0], "fps") == 0)
		status = fps_cmd(state);
	else if (strcmp(command[0], "antialiasing") == 0)
		status = antialiasing_cmd(state);
	else if (strcmp(command[0], "postprocess") == 0)
		status = post_process_cmd(command, state);
	else if (strcmp(command[0], "exit") == 0)
		status = exit_cmd(state);
	else
	{
		warning("command not found", command[0]);
		status = CS_FAIL;
	}
	ft_free_strtab(command);
	return (status);
}

void	process_command(t_state *state)
{
	t_cli				*cli;
	enum e_cmd_status	status;
	int					old_cancel_state;

	cli = &state->cli;
	pthread_mutex_lock(&cli->mutex);
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	status = exec_command(cli->command, state);
	free(cli->command);
	cli->command = NULL;
	if (status != CS_EXIT && status != CS_CRASH)
		cli->is_new_command = false;
	pthread_setcancelstate(old_cancel_state, NULL);
	pthread_mutex_unlock(&cli->mutex);
	if (status == CS_EXIT)
		exit_program(state, EXIT_SUCCESS);
	if (status == CS_CRASH)
		exit_program(state, EXIT_FAILURE);
}

static void	cli(t_state *state)
{
	char	*line;
	t_cli	*cli_ptr;

	cli_ptr = &state->cli;
	while (true)
	{
		pthread_mutex_lock(&cli_ptr->mutex);
		if (cli_ptr->is_new_command)
		{
			pthread_mutex_unlock(&cli_ptr->mutex);
			usleep(100);
			continue ;
		}
		pthread_mutex_unlock(&cli_ptr->mutex);
		line = readline("> ");
		if (!line)
		{
			pthread_mutex_lock(&cli_ptr->mutex);
			cli_ptr->is_closed = true;
			pthread_mutex_unlock(&cli_ptr->mutex);
			break ;
		}
		if (!line[0])
			continue ;
		add_history(line);
		pthread_mutex_lock(&cli_ptr->mutex);
		cli_ptr->command = strdup(line);
		cli_ptr->is_new_command = true;
		pthread_mutex_unlock(&cli_ptr->mutex);
		free(line);
	}
}

void	*start_cli(void *args)
{
	t_cli	*cli_ptr;

	cli_ptr = &((t_state *)args)->cli;
	pthread_cleanup_push(cli_cleanup, cli_ptr);
	cli(args);
	pthread_cleanup_pop(true);
	return (NULL);
}

void	init_cli(t_state *state)
{
	state->cli.command = NULL;
	state->cli.is_new_command = false;
	state->cli.is_closed = false;
	pthread_mutex_init(&state->cli.mutex, NULL);
	pthread_create(&state->cli.thread, NULL, start_cli, state);
	state->cli.is_init = true;
}
