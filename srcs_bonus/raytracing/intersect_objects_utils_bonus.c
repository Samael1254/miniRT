#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include <math.h>

double	closest_root(double root1, double root2)
{
	double	tmp;

	tmp = ft_minf(root1, root2);
	root2 = ft_maxf(root1, root2);
	root1 = tmp;
	if (ft_inff(root1, 0))
	{
		if (ft_inff(root2, 0))
			return (INFINITY);
		return (root2);
	}
	return (root1);
}

double	triangle_distance(double d, t_ray ray, t_vec3 vectors[3], t_vec3 a)
{
	double	params[2];
	t_vec3	ao;
	t_vec3	cross;

	d = 1 / d;
	ao = ft_sub_vec3(ray.origin, a);
	cross = ft_cross_vec3(ray.direction, ao);
	params[0] = d * ft_dot_vec3(vectors[1], cross);
	params[1] = -d * ft_dot_vec3(vectors[0], cross);
	if (ft_inff(params[0], 0) || ft_inff(params[1], 0) || ft_supf(params[0]
			+ params[1], 1))
		return (INFINITY);
	return (-d * ft_dot_vec3(ao, vectors[2]));
}

double	cone_delta(double params[3], t_vec3 co, t_ray ray, t_cone cone)
{
	double	u;
	double	v;
	double	w;
	double	cos2;

	u = ft_dot_vec3(co, cone.axis);
	v = ft_dot_vec3(ray.direction, cone.axis);
	w = ft_dot_vec3(co, ray.direction);
	cos2 = pow(cos(cone.slope), 2);
	params[0] = v * v - cos2 * ft_vec3_square_norm(ray.direction);
	params[1] = u * v - w * cos2;
	params[2] = u * u - ft_vec3_square_norm(co) * cos2;
	return (pow(params[1], 2) - params[0] * params[2]);
}

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
