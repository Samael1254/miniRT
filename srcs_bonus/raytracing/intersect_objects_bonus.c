#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stddef.h>

static double	closest_root(double root1, double root2)
{
	if (ft_inff(root1, 0))
		return (root2);
	return (root1);
}

double	intersect_triangle(t_ray ray, t_triangle triangle)
{
	t_vector3d	ab;
	t_vector3d	ac;
	t_vector3d	n;
	double		d;

	ab = ft_sub_vectors3d(triangle.b, triangle.a);
	ac = ft_sub_vectors3d(triangle.c, triangle.a);
	n = ft_cross_vectors3d(ab, ac);
	d = ft_dot_vectors3d(ray.direction, n);
	if (ft_equalf(d, 0))
		return (INFINITY);
}

double	cone_delta(double params[3], t_vector3d co, t_ray ray, t_cone cone)
{
	double	u;
	double	v;
	double	w;
	double	cos2;

	u = ft_dot_vectors3d(co, cone.axis);
	v = ft_dot_vectors3d(ray.direction, cone.axis);
	w = ft_dot_vectors3d(co, ray.direction);
	cos2 = pow(cos(cone.slope), 2);
	params[0] = pow(v, 2) - cos2 * ft_vector3d_square_norm(ray.direction);
	params[1] = u * v - w * cos2;
	params[2] = pow(u, 2) - ft_vector3d_square_norm(co) * cos2;
	return (pow(params[1], 2) - params[0] * params[2]);
}

double	intersect_cone(t_ray ray, t_cone cone)
{
	t_vector3d	co;
	double		params[3];
	double		delta;

	co = ft_sub_vectors3d(ray.origin, cone.pos);
	delta = cone_delta(params, co, ray, cone);
	if (ft_inff(delta, 0))
		return (INFINITY);
	delta = sqrt(delta);
	return (closest_root(-params[1] - delta, -params[1] + delta) / params[0]);
}

double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector3d	co;
	double		b;
	double		c;
	double		delta;

	co = ft_sub_vectors3d(ray.origin, sphere.pos);
	b = ft_dot_vectors3d(ray.direction, co);
	c = ft_dot_vectors3d(co, co) - pow(sphere.diameter / 2, 2);
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

	dir_dot = ft_dot_vectors3d(ray.direction, plane.normal);
	point_dot = ft_dot_vectors3d(ft_sub_vectors3d(ray.origin, plane.point),
			plane.normal);
	if (ft_equalf(dir_dot, 0) || ft_equalf(point_dot, 0))
		return (INFINITY);
	return (-point_dot / dir_dot);
}

static double	cylinder_delta(t_ray ray, t_cylinder cylinder, double params[5],
		t_vector3d vectors[3])
{
	double	h;

	vectors[0] = ft_scale_vector3d(cylinder.height, cylinder.axis);
	vectors[1] = ft_sub_vectors3d(cylinder.pos, ft_scale_vector3d(0.5,
				vectors[0]));
	vectors[2] = ft_sub_vectors3d(ray.origin, vectors[1]);
	params[0] = ft_dot_vectors3d(vectors[0], vectors[0]);
	params[1] = ft_dot_vectors3d(vectors[0], vectors[2]);
	params[2] = params[0] - pow(ft_dot_vectors3d(vectors[0], ray.direction), 2);
	params[3] = params[0] * ft_dot_vectors3d(vectors[2], ray.direction)
		- params[1] * ft_dot_vectors3d(vectors[0], ray.direction);
	params[4] = params[0] * ft_dot_vectors3d(vectors[2], vectors[2]) - params[1]
		* params[1] - pow(cylinder.diameter / 2.0, 2) * params[0];
	h = params[3] * params[3] - params[2] * params[4];
	if (h < 0.0)
		return (INFINITY);
	return (sqrt(h));
}

double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector3d	vectors[3];
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
	y = params[1] + t * ft_dot_vectors3d(vectors[0], ray.direction);
	if (y > 0.0 && y < params[0])
		return (t);
	if (y < 0.0)
		t = (0.0 - params[1]) / ft_dot_vectors3d(vectors[0], ray.direction);
	else
		t = (params[0] - params[1]) / ft_dot_vectors3d(vectors[0],
				ray.direction);
	if (ft_absf(params[3] + params[2] * t) < delta)
		return (t);
	return (INFINITY);
}

// static double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
// {
// 	t_vector3d	bo;
// 	t_vector3d	u;
// 	t_vector3d	v;
// 	double		delta;
// 	double		distance;
//
// 	bo = ft_sub_vectors3d(ray.origin, ft_sub_vectors3d(cylinder.pos,
// 				ft_scale_vector3d(-cylinder.height / 2, cylinder.axis)));
// 	u = ft_cross_vectors3d(cylinder.axis, bo);
// 	v = ft_cross_vectors3d(cylinder.axis, ray.direction);
// 	delta = pow(ft_dot_vectors3d(u, v), 2) - ft_vector3d_square_norm(v)
// 		* (ft_vector3d_square_norm(u) - pow(cylinder.diameter / 2, 2));
// 	if (ft_inff(delta, 0))
// 		return (INFINITY);
// 	delta = sqrt(delta);
// 	distance = closest_root(-ft_dot_vectors3d(u, v) - delta,
// 			-ft_dot_vectors3d(u, v) + delta) / ft_vector3d_square_norm(v);
// 	if (ft_in_rangef(ft_dot_vectors3d(cylinder.axis, bo) + distance
// 			* ft_dot_vectors3d(cylinder.axis, ray.direction), 0,
// 			cylinder.height))
// 		return (INFINITY);
// 	return (distance);
// }
