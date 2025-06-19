#ifndef MINIRT_CLI
# define MINIRT_CLI

# include "minirt_defs.h"

void	parse_command(char *line);
void	process_command(t_cli *cli);
void	init_cli(t_cli *cli);
void	*start_cli(void *state);

int		keys_cmd(void);

#endif
