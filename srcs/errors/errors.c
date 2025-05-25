/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/25 15:14:43 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void	error(const char *type, const char *msg)
{
	dprintf(2, "\e[31;1mError\e[0;1m: ");
	if (type)
		dprintf(2, "%s\e[0m: ", type);
	dprintf(2, "%s\n", msg);
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
