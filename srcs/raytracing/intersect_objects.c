#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>
#include <stddef.h>

static double	closest_root(double root1, double root2)
{
	if (ft_inff(root1, 0))
		return (root2);
	return (root1);
}

static double	intersect_sphere(t_ray ray, t_sphere sphere)
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

static double	intersect_plane(t_ray ray, t_plane plane)
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

static double	calculate_cylinder_params(t_ray ray, t_cylinder cylinder,
		double params[5], t_vector3d vectors[3])
{
	double	h;

	vectors[0] = ft_scale_vector3d(cylinder.height,
			ft_normalize_vector3d(cylinder.axis));
	vectors[0] = ft_scale_vector3d(1.0, vectors[0]);
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
		return (-1.0);
	return (sqrt(h));
}

static double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector3d	vectors[3];
	double		params[5];
	double		t;
	double		y;
	double		h;

	h = calculate_cylinder_params(ray, cylinder, params, vectors);
	if (h < 0.0)
		return (INFINITY);
	t = (-params[3] - h) / params[2];
	y = params[1] + t * ft_dot_vectors3d(vectors[0], ray.direction);
	if (y > 0.0 && y < params[0])
		return (t);
	if (y < 0.0)
		t = (0.0 - params[1]) / ft_dot_vectors3d(vectors[0], ray.direction);
	else
		t = (params[0] - params[1]) / ft_dot_vectors3d(vectors[0],
				ray.direction);
	if (ft_absf(params[3] + params[2] * t) < h)
		return (t);
	return (INFINITY);
}

double	intersect_object(t_ray ray, t_object object)
{
	if (object.type == SPHERE)
		return (intersect_sphere(ray, *(t_sphere *)object.object_r));
	if (object.type == PLANE)
		return (intersect_plane(ray, *(t_plane *)object.object_r));
	if (object.type == CYLINDER)
		return (intersect_cylinder(ray, *(t_cylinder *)object.object_r));
	warning("invalid object", "object type not found");
	return (INFINITY);
}
