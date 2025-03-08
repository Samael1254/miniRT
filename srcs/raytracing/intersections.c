#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>

static double	intersect_sphere(t_ray ray, t_sphere sphere)
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

// static double	intersect_sphere(t_ray ray, t_sphere sphere)
// {
// 	t_vector3d	oc;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		delta;
//
// 	a = ft_dot_vectors3d(ray.direction, ray.direction);
// 	oc = ft_sub_vectors3d(ray.origin, sphere.pos);
// 	b = ft_dot_vectors3d(ray.direction, oc);
// 	c = ft_dot_vectors3d(oc, oc) - pow(sphere.diameter / 2, 2);
// 	delta = b * b - a * c;
// 	if (delta <= 0)
// 		return (INFINITY);
// 	printf("hit sphere\n");
// 	return ((-b - sqrt(delta)) / a);
// }

static double	intersect_plane(t_ray ray, t_plane plane)
{
	double	dir_dot;
	double	point_dot;

	dir_dot = ft_dot_vectors3d(ray.direction, plane.normal);
	point_dot = ft_dot_vectors3d(ft_sub_vectors3d(ray.origin, plane.point),
			plane.normal);
	if (dir_dot == 0. || point_dot == 0.)
		return (INFINITY);
	return (-point_dot / dir_dot);
}

static double	intersect_cylinder(t_ray ray, t_cylinder cylinder)
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
	dist = (-udv - sqrt(pow(udv, 2) - ft_vector3d_square_norm(u)
				* (ft_vector3d_square_norm(v) - pow(cylinder.diameter / 2, 2))))
		/ ft_vector3d_square_norm(u);
	height_dist = ft_dot_vectors3d(cylinder.axis,
			ft_add_vectors3d(ft_scale_vector3d(dist, ray.direction),
				centers_vect));
	if (height_dist < -cylinder.height / 2 || height_dist > cylinder.height / 2)
		return (INFINITY);
	return (dist);
}

static double	intersect_object(t_ray ray, t_object object)
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

t_intersection	no_intersection(t_ray ray)
{
	t_intersection	inter;

	inter.color = get_sky_color(ray);
	inter.point = ft_init_vector3d(INFINITY);
	return (inter);
}

t_intersection	intersect_scene(t_ray ray, t_list *objects)
{
	double			cur_distance;
	double			distance_min;
	t_object		*cur_object;
	t_object		*closest_object;
	t_intersection	inter;

	distance_min = INFINITY;
	while (objects)
	{
		cur_object = (t_object *)objects->data;
		cur_distance = intersect_object(ray, *cur_object);
		if (ft_in_rangef(cur_distance, RAY_REACH_MIN, distance_min))
		{
			distance_min = cur_distance;
			closest_object = cur_object;
		}
		objects = objects->next;
	}
	if (!ft_in_rangef(distance_min, RAY_REACH_MIN, RAY_REACH_MAX))
		return (no_intersection(ray));
	inter.color = closest_object->color;
	inter.point = ft_add_vectors3d(ray.origin, ft_scale_vector3d(distance_min,
				ray.direction));
	return (inter);
}
