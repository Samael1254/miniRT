/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_base.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_raytracing.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_state	state;

	check_arguments(argc, argv);
	init_state(&state, argv[1]);
	ray_tracing(&state);
	state.end_time = get_time(&state);
	printf("Frame render time: %ld ms\n", get_time_diff(state.end_time,
			state.start_time));
	info(NULL, "done, press ESC to close, H for help");
	loop_events(&state);
	warning("unusal exit", "program should be closed with ESC or cross");
	exit_program(&state, EXIT_FAILURE);
}
