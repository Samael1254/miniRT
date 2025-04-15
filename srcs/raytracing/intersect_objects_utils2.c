/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects_utils2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt_defs.h"
#include "minirt_intersections.h"
#include <math.h>

double	intersect_cylinder_body(t_ray ray, t_cylinder cylinder)
{
	t_vec3	vectors[3];
	double	params[5];
	double	t;
	double	y;
	double	delta;

	delta = cylinder_delta(ray, cylinder, params, vectors);
	if (delta == INFINITY)
		return (INFINITY);
	t = closest_root((-params[3] - delta) / params[2],
			(-params[3] + delta) / params[2]);
	y = params[1] + t * ft_dot_vec3(vectors[0], ray.direction);
	if (ft_in_rangef(y, 0, params[0]))
		return (t);
	if (ft_inff(y, 0))
		t = -params[1] / ft_dot_vec3(vectors[0], ray.direction);
	else
		t = (params[0] - params[1]) / ft_dot_vec3(vectors[0], ray.direction);
	if (ft_absf(params[3] + params[2] * t) < delta)
		return (t);
	return (INFINITY);
}
