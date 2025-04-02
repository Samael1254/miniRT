#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_intersections_bonus.h"
#include <math.h>
#include <stdbool.h>

static t_vec3	ft_inverse_vec3(t_vec3 v)
{
	t_vec3	u;

	u.x = 1 / v.x;
	u.y = 1 / v.y;
	u.z = 1 / v.z;
	return (u);
}

static void	ft_vec3_to_array(t_vec3 v, double a[3])
{
	a[0] = v.x;
	a[1] = v.y;
	a[2] = v.z;
}

static void	ft_swapf(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static bool	aabb_roots(double tbox[2], const double dets[3],
		const double omin[3], const double omax[3])
{
	double	tplane[2];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (dets[i] == NAN)
		{
			if (ft_supf(omin[i], 0) || ft_inff(omax[i], 0))
				return (false);
			i++;
			continue ;
		}
		tplane[0] = omin[i] * dets[i];
		tplane[1] = omax[i] * dets[i];
		if (ft_supf(tplane[0], tplane[1]))
			ft_swapf(&tplane[0], &tplane[1]);
		tbox[0] = fmax(tbox[0], tplane[0]);
		tbox[1] = fmin(tbox[1], tplane[1]);
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

	ft_vec3_to_array(ft_sub_vec3(box.min, ray.origin), omin);
	ft_vec3_to_array(ft_sub_vec3(box.max, ray.origin), omax);
	ft_vec3_to_array(ft_inverse_vec3(ray.direction), dets);
	tbox[0] = INFINITY;
	tbox[1] = INFINITY;
	if (!aabb_roots(tbox, dets, omin, omax))
		return (INFINITY);
	return (closest_root(tbox[0], tbox[1]));
}
