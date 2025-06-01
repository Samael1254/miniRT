/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/06/02 00:48:03 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"
#include "minirt_defs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	error(const char *type, const char *msg, t_state *state)
{
	dprintf(2, "\e[31;1mError\e[0;1m: ");
	if (type)
		dprintf(2, "%s\e[0m: ", type);
	dprintf(2, "%s\n", msg);
	exit_program(state, EXIT_FAILURE);
}

void	warning(const char *type, const char *msg)
{
	dprintf(2, "\e[33;1mWarning\e[0;1m: ");
	if (type)
		dprintf(2, "%s\e[0m: ", type);
	dprintf(2, "%s\n", msg);
}

void	info(const char *type, const char *msg)
{
	dprintf(2, "\e[34;1mInfo\e[0;1m: ");
	if (type)
		dprintf(2, "%s\e[0m: ", type);
	dprintf(2, "%s\n", msg);
}
