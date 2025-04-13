#include "ft_algebra.h"
#include "minirt_defs.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

double	cylinder_delta(t_ray ray, t_cylinder cylinder, double params[5],
		t_vec3 vectors[3])
{
	double	h;

	vectors[0] = ft_scale_vec3(cylinder.height, cylinder.axis);
	vectors[1] = ft_sub_vec3(cylinder.pos, ft_scale_vec3(0.5, vectors[0]));
	vectors[2] = ft_sub_vec3(ray.origin, vectors[1]);
	params[0] = ft_dot_vec3(vectors[0], vectors[0]);
	params[1] = ft_dot_vec3(vectors[0], vectors[2]);
	params[2] = params[0] - pow(ft_dot_vec3(vectors[0], ray.direction), 2);
	params[3] = params[0] * ft_dot_vec3(vectors[2], ray.direction) - params[1]
		* ft_dot_vec3(vectors[0], ray.direction);
	params[4] = params[0] * ft_dot_vec3(vectors[2], vectors[2]) - params[1]
		* params[1] - pow(cylinder.diameter / 2.0, 2) * params[0];
	h = pow(params[3], 2) - params[2] * params[4];
	if (h < 0.0)
		return (INFINITY);
	return (sqrt(h));
}

double	intersect_cap(t_ray ray, t_cylinder cylinder, bool top)
{
	t_vec3	center;
	t_vec3	normal;
	double	denom;
	double	t;
	t_vec3	hit;

	normal = ft_normalize_vec3(cylinder.axis);
	if (top)
		center = ft_add_vec3(cylinder.pos,
				ft_scale_vec3(cylinder.height / 2, normal));
	else
		center = ft_sub_vec3(cylinder.pos,
				ft_scale_vec3(cylinder.height / 2, normal));
	denom = ft_dot_vec3(normal, ray.direction);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	t = ft_dot_vec3(ft_sub_vec3(center, ray.origin), normal) / denom;
	if (t < 0)
		return (INFINITY);
	hit = ft_add_vec3(ray.origin, ft_scale_vec3(t, ray.direction));
	if (ft_vec3_norm(ft_sub_vec3(hit, center)) <= cylinder.diameter / 2.0)
		return (t);
	return (INFINITY);
}
