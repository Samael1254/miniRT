/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

double	intersect_triangle(t_ray ray, t_bvh_tr triangle, const t_vec3 *vertices)
{
	t_vec3	tr_vertices[3];
	t_vec3	vectors[3];
	double	d;

	tr_vertices[0] = vertices[triangle.vertices_id[0]];
	tr_vertices[1] = vertices[triangle.vertices_id[1]];
	tr_vertices[2] = vertices[triangle.vertices_id[2]];
	vectors[0] = ft_sub_vec3(tr_vertices[1], tr_vertices[0]);
	vectors[1] = ft_sub_vec3(tr_vertices[2], tr_vertices[0]);
	vectors[2] = ft_cross_vec3(vectors[0], vectors[1]);
	d = ft_dot_vec3(ray.direction, vectors[2]);
	if (ft_equalf(d, 0))
		return (INFINITY);
	return (triangle_distance(d, ray, vectors, tr_vertices[0]));
}
