#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_intersections_bonus.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

t_vec3	ft_inverse_vec3(t_vec3 v)
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

void	ft_swapf(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_ivec2	hit_box(bool hit, bool print)
{
	t_ivec2		ret;
	static int	nhit;
	static int	ntot;

	if (!print)
	{
		ntot++;
		if (hit)
			nhit++;
	}
	ret.x = nhit;
	ret.y = ntot;
	return (ret);
}

bool	aabb_roots(double tbox[2], const double dets[3], const double omin[3],
		const double omax[3])
{
	double	tplane[2];
	int		i;

	i = 0;
	while (i < 3)
	{
		// if (isinf(dets[i]))
		// {
		// 	if (ft_supf(omin[i], 0) || ft_inff(omax[i], 0))
		// 		return (false);
		// 	i++;
		// 	continue ;
		// }
		tplane[0] = omin[i] * dets[i];
		tplane[1] = omax[i] * dets[i];
		if (ft_supf(tplane[0], tplane[1]))
			ft_swapf(&tplane[0], &tplane[1]);
		tbox[0] = fmax(tbox[0], tplane[0]);
		tbox[1] = fmin(tbox[1], tplane[1]);
		if (tbox[0] > tbox[1])
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
	{
		hit_box(false, false);
		return (INFINITY);
	}
	hit_box(true, false);
	t = closest_root(tbox[0], tbox[1]);
	return (t);
}

// double	intersect_aabb(t_ray r, t_aabb box)
// {
// 	double	tmin;
// 	double	tmax;
// 	double	tymin;
// 	double	tymax;
// 	double	tzmin;
// 	double	tzmax;
//
// 	tmin = (box.min.x - r.origin.x) / r.direction.x;
// 	tmax = (box.max.x - r.origin.x) / r.direction.x;
// 	if (tmin > tmax)
// 		ft_swapf(&tmin, &tmax);
// 	tymin = (box.min.y - r.origin.y) / r.direction.y;
// 	tymax = (box.max.y - r.origin.y) / r.direction.y;
// 	if (tymin > tymax)
// 		ft_swapf(&tymin, &tymax);
// 	if ((tmin > tymax) || (tymin > tmax))
// 	{
// 		hit_box(false, false);
// 		return (INFINITY);
// 	}
// 	if (tymin > tmin)
// 		tmin = tymin;
// 	if (tymax < tmax)
// 		tmax = tymax;
// 	tzmin = (box.min.z - r.origin.z) / r.direction.z;
// 	tzmax = (box.max.z - r.origin.z) / r.direction.z;
// 	if (tzmin > tzmax)
// 		ft_swapf(&tzmin, &tzmax);
// 	if ((tmin > tzmax) || (tzmin > tmax))
// 	{
// 		hit_box(false, false);
// 		return (INFINITY);
// 	}
// 	if (tzmin > tmin)
// 		tmin = tzmin;
// 	if (tzmax < tmax)
// 		tmax = tzmax;
// 	hit_box(true, false);
// 	return (tmin);
// }
