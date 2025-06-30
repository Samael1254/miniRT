#ifndef MINIRT_CLI
# define MINIRT_CLI

# include "minirt_defs.h"

void				process_command(t_state *state);
void				init_cli(t_state *state);
void				*start_cli(void *state);

enum e_cmd_status	keys_cmd(char **command);
enum e_cmd_status	screenshot_cmd(char **command, t_state *state);
enum e_cmd_status	fps_cmd(char **command, t_state *state);
enum e_cmd_status	antialiasing_cmd(char **command, t_state *state);
enum e_cmd_status	post_process_cmd(char **command, t_state *state);
enum e_cmd_status	exit_cmd(char **command);

char				*pp_filter_name(enum e_post_process id);
bool				check_command_size(int size, int max_size);
enum e_cmd_status	cmd_help(const char *text, int cmd_len);

#endif
