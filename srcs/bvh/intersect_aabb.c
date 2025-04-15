/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_aabb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs.h"
#include "minirt_intersections.h"
#include <math.h>
#include <stdbool.h>

static t_vec3	ft_inverse_vec3(t_vec3 v)
{
	t_vec3	u;

	u = ft_init_vec3(INFINITY);
	if (!ft_equalf(v.x, 0))
		u.x = 1. / v.x;
	if (!ft_equalf(v.y, 0))
		u.y = 1. / v.y;
	if (!ft_equalf(v.z, 0))
		u.z = 1. / v.z;
	return (u);
}

void	ft_vec3_to_array(t_vec3 v, double a[3])
{
	a[0] = v.x;
	a[1] = v.y;
	a[2] = v.z;
}

t_vec3	ft_array_to_vec3(const double a[3])
{
	t_vec3	v;

	v.x = a[0];
	v.y = a[1];
	v.z = a[2];
	return (v);
}

// static void	ft_swapf(double *a, double *b)
// {
// 	double	temp;
//
// 	temp = *a;
// 	*a = *b;
// 	*b = temp;
// }

bool	aabb_roots(double tbox[2], const double dets[3], const double omin[3],
		const double omax[3])
{
	double	tplane[2];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (isinf(dets[i]))
		{
			if (ft_supf(omin[i], 0) || ft_inff(omax[i], 0))
				return (false);
			i++;
			continue ;
		}
		tplane[0] = omin[i] * dets[i];
		tplane[1] = omax[i] * dets[i];
		tbox[0] = fmax(tbox[0], fmin(tplane[0], tplane[1]));
		tbox[1] = fmin(tbox[1], fmax(tplane[0], tplane[1]));
		if (ft_supf(tbox[0], tbox[1]))
			return (false);
		i++;
	}
	return (true);
}

double	intersect_aabb(t_ray ray, t_aabb box)
{
	double	omin[3];
	double	omax[3];
	double	dets[3];
	double	tbox[2];
	double	t;

	ft_vec3_to_array(ft_sub_vec3(box.min, ray.origin), omin);
	ft_vec3_to_array(ft_sub_vec3(box.max, ray.origin), omax);
	ft_vec3_to_array(ft_inverse_vec3(ray.direction), dets);
	tbox[0] = 0.0f;
	tbox[1] = INFINITY;
	if (!aabb_roots(tbox, dets, omin, omax))
		return (INFINITY);
	t = closest_root(tbox[0], tbox[1]);
	return (t);
}
