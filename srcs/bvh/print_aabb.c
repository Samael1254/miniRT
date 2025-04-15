/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aabb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_defs.h"

#include <stdio.h>

static void	print_vec3(t_vec3 vec)
{
	printf("%.5f,%.5f,%.5f\n", vec.x, vec.y, vec.z);
}

void	print_aabb(t_aabb aabb)
{
	printf("aabb_min => ");
	print_vec3(aabb.min);
	printf("aabb_max => ");
	print_vec3(aabb.max);
}
