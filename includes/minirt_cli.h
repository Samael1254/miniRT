#ifndef MINIRT_CLI
# define MINIRT_CLI

# include "minirt_defs.h"

void				process_command(t_state *state);
void				init_cli(t_state *state);
void				*start_cli(void *state);

enum e_cmd_status	keys_cmd(void);
enum e_cmd_status	exit_cmd(t_state *state);

#endif
