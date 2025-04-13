#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>
#include <stddef.h>
#include <stdbool.h>

static double	closest_root(double root1, double root2)
{
	if (ft_inff(root1, 0))
		return (root2);
	return (root1);
}

double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vec3	co;
	double	b;
	double	c;
	double	delta;

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

double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	double	t_body;
	double	t_cap1;
	double	t_cap2;
	double	t;

	t_body = intersect_cylinder_body(ray, cylinder);
	t_cap1 = intersect_cap(ray, cylinder, true);
	t_cap2 = intersect_cap(ray, cylinder, false);
	t = INFINITY;
	if (t_body > 0 && t_body < t)
		t = t_body;
	if (t_cap1 > 0 && t_cap1 < t)
		t = t_cap1;
	if (t_cap2 > 0 && t_cap2 < t)
		t = t_cap2;
	return (t);
}
