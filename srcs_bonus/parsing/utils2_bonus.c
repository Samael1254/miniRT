/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chars.h"
#include "ft_math.h"
#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include <stdbool.h>

bool	is_norm_vector_valid(t_vec3 vec)
{
	if (!ft_equalf(ft_vec3_norm(vec), 1))
		return (false);
	return (true);
}

/*
 *	Check if a vector is in the range min and max (excluded)
 *	Returns (0) if not
 *	Returns (1) if yes
 * */
bool	is_vec3_in_range(t_vec3 vec, double min, double max)
{
	if (vec.x < min || vec.x > max)
		return (false);
	if (vec.y < min || vec.y > max)
		return (false);
	if (vec.z < min || vec.z > max)
		return (false);
	return (true);
}

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
			error("invalid parameter", "parameters must be numbers", state);
		}
		i++;
	}
}
