#ifndef MINIRT_CLI
# define MINIRT_CLI

# include "minirt_defs.h"

void	process_command(t_cli *cli);
void	init_cli(t_cli *cli);
void	cli(t_cli *cli);
void	*start_cli(void *state);

#endif
