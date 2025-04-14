/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general_objects_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chars.h"
#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"

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
