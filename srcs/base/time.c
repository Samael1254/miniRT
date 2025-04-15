/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval	get_time(t_state *state)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error(NULL, "gettimofday failed", state);
	return (time);
}

long	get_time_diff(struct timeval time, struct timeval start_time)
{
	time_t		s;
	suseconds_t	us;

	s = time.tv_sec - start_time.tv_sec;
	us = time.tv_usec - start_time.tv_usec;
	return (s * 1000 + us / 1000);
}

char	*get_fps_string(long time)
{
	char	*str;
	double	fps;

	fps = 1000 / (double)time;
	str = ft_calloc(16, sizeof(char));
	if (!str)
		return (NULL);
	sprintf(str, "%.2f FPS", fps);
	return (str);
}
