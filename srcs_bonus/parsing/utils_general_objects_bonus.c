#include "ft_chars.h"
#include "ft_strings.h"
#include "minirt_bonus.h"

void	ambiant_light_checker(t_state *state, char **split)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(split[1]);
	while (i < len)
	{
		if (!ft_isdigit(split[1][i]) && split[1][i] != '.')
		{
			ft_free_strtab(split);
			error("ambiant light", "intensity isn't formatted", state);
		}
		i++;
	}
}
