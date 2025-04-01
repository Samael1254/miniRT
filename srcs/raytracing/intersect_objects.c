#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs.h"
#include <math.h>
#include <stddef.h>

static double	closest_root(double root1, double root2)
{
	if (ft_inff(root1, 0))
		return (root2);
	return (root1);
}

double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vec3	co;
	double		b;
	double		c;
	double		delta;

	co = ft_sub_vec3(ray.origin, sphere.pos);
	b = ft_dot_vec3(ray.direction, co);
	c = ft_dot_vec3(co, co) - pow(sphere.diameter / 2, 2);
	delta = b * b - c;
	if (ft_inff(delta, 0))
		return (INFINITY);
	delta = sqrt(delta);
	return (closest_root(-b - delta, -b + delta));
}

double	intersect_plane(t_ray ray, t_plane plane)
{
	double	dir_dot;
	double	point_dot;

	dir_dot = ft_dot_vec3(ray.direction, plane.normal);
	point_dot = ft_dot_vec3(ft_sub_vec3(ray.origin, plane.point),
			plane.normal);
	if (ft_equalf(dir_dot, 0) || ft_equalf(point_dot, 0))
		return (INFINITY);
	return (-point_dot / dir_dot);
}

static double	cylinder_delta(t_ray ray, t_cylinder cylinder, double params[5],
		t_vec3 vectors[3])
{
	double	h;

	vectors[0] = ft_scale_vec3(cylinder.height, cylinder.axis);
	vectors[1] = ft_sub_vec3(cylinder.pos, ft_scale_vec3(0.5,
				vectors[0]));
	vectors[2] = ft_sub_vec3(ray.origin, vectors[1]);
	params[0] = ft_dot_vec3(vectors[0], vectors[0]);
	params[1] = ft_dot_vec3(vectors[0], vectors[2]);
	params[2] = params[0] - pow(ft_dot_vec3(vectors[0], ray.direction), 2);
	params[3] = params[0] * ft_dot_vec3(vectors[2], ray.direction)
		- params[1] * ft_dot_vec3(vectors[0], ray.direction);
	params[4] = params[0] * ft_dot_vec3(vectors[2], vectors[2]) - params[1]
		* params[1] - pow(cylinder.diameter / 2.0, 2) * params[0];
	h = params[3] * params[3] - params[2] * params[4];
	if (h < 0.0)
		return (INFINITY);
	return (sqrt(h));
}

double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vec3	vectors[3];
	double		params[5];
	double		t;
	double		y;
	double		delta;

	delta = cylinder_delta(ray, cylinder, params, vectors);
	if (delta == INFINITY)
		return (INFINITY);
	t = (-params[3] - delta) / params[2];
	if (ft_inff(t, 0))
		t = (-params[3] + delta) / params[2];
	y = params[1] + t * ft_dot_vec3(vectors[0], ray.direction);
	if (y > 0.0 && y < params[0])
		return (t);
	if (y < 0.0)
		t = (0.0 - params[1]) / ft_dot_vec3(vectors[0], ray.direction);
	else
		t = (params[0] - params[1]) / ft_dot_vec3(vectors[0],
				ray.direction);
	if (ft_absf(params[3] + params[2] * t) < delta)
		return (t);
	return (INFINITY);
}

// static double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
// {
// 	t_vec3	bo;
// 	t_vec3	u;
// 	t_vec3	v;
// 	double		delta;
// 	double		distance;
//
// 	bo = ft_sub_vec3(ray.origin, ft_sub_vec3(cylinder.pos,
// 				ft_scale_vec3(-cylinder.height / 2, cylinder.axis)));
// 	u = ft_cross_vec3(cylinder.axis, bo);
// 	v = ft_cross_vec3(cylinder.axis, ray.direction);
// 	delta = pow(ft_dot_vec3(u, v), 2) - ft_vec3_square_norm(v)
// 		* (ft_vec3_square_norm(u) - pow(cylinder.diameter / 2, 2));
// 	if (ft_inff(delta, 0))
// 		return (INFINITY);
// 	delta = sqrt(delta);
// 	distance = closest_root(-ft_dot_vec3(u, v) - delta,
// 			-ft_dot_vec3(u, v) + delta) / ft_vec3_square_norm(v);
// 	if (ft_in_rangef(ft_dot_vec3(cylinder.axis, bo) + distance
// 			* ft_dot_vec3(cylinder.axis, ray.direction), 0,
// 			cylinder.height))
// 		return (INFINITY);
// 	return (distance);
// }
