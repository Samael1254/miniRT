#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

void	cli(void)
{
	const char	*line;

	line = readline("> ");
	if (!line)
		return ;
	if (line[0])
		add_history(line);
}
