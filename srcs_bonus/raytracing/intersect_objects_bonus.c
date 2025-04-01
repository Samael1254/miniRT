#include "ft_math.h"
#include "minirt_intersections_bonus.h"
#include <math.h>

double	intersect_cone(t_ray ray, t_cone cone)
{
	t_vec3	co;
	double	params[3];
	double	delta;

	co = ft_sub_vec3(ray.origin, cone.pos);
	delta = cone_delta(params, co, ray, cone);
	if (ft_equalf(params[0], 0))
		return (-params[2] / (2 * params[1]));
	if (ft_inff(delta, 0))
		return (INFINITY);
	delta = sqrt(delta);
	return (closest_root((-params[1] - delta) / params[0], (-params[1] + delta)
			/ params[0]));
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
	point_dot = ft_dot_vec3(ft_sub_vec3(ray.origin, plane.point), plane.normal);
	if (ft_equalf(dir_dot, 0) || ft_equalf(point_dot, 0))
		return (INFINITY);
	return (-point_dot / dir_dot);
}

double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vec3	vectors[3];
	double	params[5];
	double	t;
	double	y;
	double	delta;

	delta = cylinder_delta(ray, cylinder, params, vectors);
	if (delta == INFINITY)
		return (INFINITY);
	t = closest_root((-params[3] - delta) / params[2], (-params[3] + delta)
			/ params[2]);
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

double	intersect_triangle(t_ray ray, t_triangle triangle)
{
	t_vec3	vertices[3];
	t_vec3	vectors[3];
	double	d;

	vertices[0] = triangle.vertices[0];
	vertices[1] = triangle.vertices[1];
	vertices[2] = triangle.vertices[2];
	vectors[0] = ft_sub_vec3(vertices[1], vertices[0]);
	vectors[1] = ft_sub_vec3(vertices[2], vertices[0]);
	vectors[2] = ft_cross_vec3(vectors[0], vectors[1]);
	d = ft_dot_vec3(ray.direction, vectors[2]);
	if (ft_equalf(d, 0))
		return (INFINITY);
	return (triangle_distance(d, ray, vectors, vertices[0]));
}
