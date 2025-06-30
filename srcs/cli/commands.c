#include "ft_math.h"
#include "ft_strings.h"
#include "minirt_base.h"
#include "minirt_cli.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum e_cmd_status	keys_cmd(void)
{
	printf("-- Keybindings --\n");
	printf("- Move: WASD\n");
	printf("- Zoom: Mouse wheel\n");
	printf("- Rotate: ALT + WASD\n");
	printf("- Change movement speed: UP/DOWN\n");
	printf("- Change rotation speed: LEFT/RIGHT\n");
	printf("- Show source light(s): L\n");
	printf("- Change post-process: P (Shift-P to go backwards)\n");
	printf("- Anti-aliasing: K\n");
	printf("- Show FPS: F\n");
	printf("- Save image: SPACE\n");
	printf("- Exit program: ESC\n");
	return (CS_OK);
}

enum e_cmd_status	screenshot_cmd(t_state *state)
{
	save_image(state);
	return (CS_OK);
}

enum e_cmd_status	fps_cmd(t_state *state)
{
	toggle_fps(state);
	if (state->keys_state.toggle_fps)
		info("Show FPS", "\e[32mON\e[0m");
	else
		info("Show FPS", "\e[31mOFF\e[0m");
	return (CS_OK);
}

enum e_cmd_status	antialiasing_cmd(t_state *state)
{
	toggle_aa(state);
	if (state->keys_state.toggle_aa)
		info("Anti-aliasing", "\e[32mON\e[0m");
	else
		info("Anti-aliasing", "\e[31mOFF\e[0m");
	return (CS_OK);
}

enum e_cmd_status	post_process_cmd(char **command, t_state *state)
{
	int	cmd_len;

	cmd_len = ft_strtab_size(command);
	if (cmd_len == 1)
	{
		state->post_process = (state->post_process + 1) % NB_FILTERS;
		if (state->post_process != PP_NONE)
			post_process(state);
		reload_image(state);
		info("Post process filter", pp_filter_name(state->post_process));
		return (CS_OK);
	}
	if (strcmp(command[1], "list") == 0)
	{
		if (cmd_len > 2)
			return (warning("too many arguments",
					"no argument expected after 'list'"), CS_FAIL);
		printf("-- Post process filters IDs --\n");
		printf("- None: 0\n");
		printf("- Gamma correction: 1\n");
		printf("- Negative: 2\n");
		printf("- Vignette: 3\n");
		printf("- Sepia: 4\n");
		printf("- Grayscale: 5\n");
		printf("- Poster: 6\n");
		printf("- Scanlines: 7\n");
		printf("- Black and white: 8\n");
		printf("- High saturation: 9\n");
		printf("- Dark: 10\n");
	}
	else if (strcmp(command[1], "info") == 0)
	{
		if (cmd_len > 2)
			return (warning("too many arguments",
					"no argument expected after 'info'"), CS_FAIL);
		info("Post process filter", pp_filter_name(state->post_process));
	}
	else if (strcmp(command[1], "set") == 0)
	{
		if (cmd_len < 3)
			return (warning("missing argument", "index needed after set"),
				CS_FAIL);
		if (cmd_len > 3)
			return (warning("too many arguments",
					"no argument expected after 'set [index]'"), CS_FAIL);
		if (!ft_str_is_number(command[2]))
			return (warning("invalid index", "must be a number"), CS_FAIL);
		if (!ft_in_range(atoi(command[2]), 0, NB_FILTERS - 1))
			return (warning("invalid index",
					"must be between 0 and 10 (type 'postprocess list' for more info)"),
				CS_FAIL);
		state->post_process = atoi(command[2]);
		if (state->post_process != PP_NONE)
			post_process(state);
		reload_image(state);
		info("Post process filter", pp_filter_name(state->post_process));
	}
	else if (strcmp(command[1], "help") == 0)
	{
		if (cmd_len > 2)
			return (warning("too many arguments",
					"no argument expected after 'help'"), CS_FAIL);
		printf("Change or get information about the post-processing of the scene.\n");
		printf("With no argument, it changes the filter to the next one.\n");
		printf("Arguments:\n");
		printf("- list: show all available filters\n");
		printf("- info: display the name of the current filter\n");
		printf("- set [index]: change to the filter corresponding to 'index'\n");
	}
	else
		return (warning("unknown argument", command[1]), CS_FAIL);
	return (CS_OK);
}

enum e_cmd_status	exit_cmd(t_state *state)
{
	(void)state;
	return (CS_EXIT);
}
