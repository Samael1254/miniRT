/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 19:21:06 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
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
	char	*scene_name;

	check_arguments(argc, argv);
	if (argc > 1)
		scene_name = ft_strdup(argv[1]);
	else
		scene_name = select_scene();
	init_state(&state, scene_name);
	free(scene_name);
	ray_tracing(&state);
	loop_events(&state);
	warning("unusal exit", "program should be closed with ESC or cross");
	exit_program(&state, EXIT_FAILURE);
}
