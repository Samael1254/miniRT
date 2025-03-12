#include "ft_chars.h"
#include "ft_strings.h"
#include "minirt.h"
#include <stdbool.h>

bool	ft_check_error_line(char **split, int len)
{
	int	split_len;

	split_len = ft_strtab_size(split);
	if (split_len != len || *split[split_len - 1] == '\n')
	{
		ft_free_strtab(split);
		return (false);
	}
	return (true);
}

/**	This function checks if a split initialy formatted as XXX,XXX,XXX
 * contains numbers of '-' or '+'
 *	Splitted on ','
 *	Returns false if the data isn't correct
 *	Returns true if it's correct
 * */
bool	ft_check_split_data(char **split)
{
	int	i;

	if (!split)
		return (false);
	if (ft_strtab_size(split) != 3)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!*split[i])
			return (false);
		if (!ft_isdigit(*split[i]) && *split[i] != '-' && *split[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

void	check_line(t_state *state, char **split, int split_len)
{
	int	i;

	i = 1;
	while (i < split_len)
	{
		if (!ft_isdigit(*split[i]) && *split[i] != '-' && *split[i] != '+')
		{
			ft_free_strtab(split);
			error(NULL, "something isn't a number", state);
		}
		i++;
	}
}
