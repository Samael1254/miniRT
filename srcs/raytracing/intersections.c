#include "ft_algebra.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>

double	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vector3d	dist;
	double		dist_proj;
	double		inner_dist;

	dist = ft_sub_vectors3d(sphere.pos, ray.origin);
	dist_proj = ft_dot_vectors3d(ray.direction, dist);
	inner_dist = pow(dist_proj, 2) + pow(sphere.diameter / 2, 2)
		- ft_vector3d_square_norm(dist);
	if (inner_dist < 0.0)
		return (INFINITY);
	return (dist_proj - sqrt(inner_dist));
}

double	intersect_plane(t_ray ray, t_plane plane)
{
	double	dir_dot;
	double	point_dot;

	dir_dot = ft_dot_vectors3d(ray.direction, plane.normal);
	if (dir_dot == 0.)
		return (INFINITY);
	point_dot = ft_dot_vectors3d(ft_sub_vectors3d(ray.origin, plane.point),
			plane.normal);
	return (-point_dot / dir_dot);
}

double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	double		dist;
	double		height_dist;
	t_vector3d	u;
	t_vector3d	v;
	double		udv;
	t_vector3d	centers_vect;

	u = ft_cross_vectors3d(cylinder.axis, ray.direction);
	if (ft_vector3d_norm(u) == 0.)
		return (INFINITY);
	centers_vect = ft_sub_vectors3d(ray.origin, cylinder.pos);
	v = ft_cross_vectors3d(cylinder.axis, centers_vect);
	udv = ft_dot_vectors3d(u, v);
	dist = (udv - sqrt(pow(udv, 2) - ft_vector3d_square_norm(u)
				* (ft_vector3d_square_norm(v) - pow(cylinder.diameter / 2, 2))))
		/ ft_vector3d_square_norm(u);
	height_dist = ft_dot_vectors3d(cylinder.axis,
			ft_add_vectors3d(ft_scale_vector3d(dist, ray.direction),
				centers_vect));
	if (height_dist < -cylinder.height / 2 || height_dist > cylinder.height / 2)
		return (INFINITY);
	return (dist);
}

double	intersect_object(t_ray ray, void *obj_data)
{
	t_object	object;

	object = *(t_object *)obj_data;
	if (object.type == SPHERE)
		return (intersect_sphere(ray, *(t_sphere *)object.object_r));
	if (object.type == PLANE)
		return (intersect_plane(ray, *(t_plane *)object.object_r));
	if (object.type == CYLINDER)
		return (intersect_cylinder(ray, *(t_cylinder *)object.object_r));
	error("invalid object", "object type not found");
	return (INFINITY);
}

double	intersect_scene(t_ray ray, t_list *objects)
{
	double	distance;

	distance = INFINITY;
	while (objects)
	{
		distance = fmin(distance, intersect_object(ray, objects->data));
		objects = objects->next;
	}
	return (distance);
}
