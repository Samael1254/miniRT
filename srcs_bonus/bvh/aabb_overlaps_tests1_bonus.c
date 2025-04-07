#include "ft_algebra.h"
#include <math.h>
#include <stdbool.h>

bool	axis1(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[0], edges[0]);
	p[0] = ft_dot_vec3(axis, r_vertices[0]);
	p[1] = ft_dot_vec3(axis, r_vertices[1]);
	radius = extent.y * fabs(edges[0].z) + extent.z * fabs(edges[0].y);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis2(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[0], edges[1]);
	p[0] = ft_dot_vec3(axis, r_vertices[1]);
	p[1] = ft_dot_vec3(axis, r_vertices[2]);
	radius = extent.y * fabs(edges[1].z) + extent.z * fabs(edges[1].y);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis3(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[0], edges[2]);
	p[0] = ft_dot_vec3(axis, r_vertices[2]);
	p[1] = ft_dot_vec3(axis, r_vertices[0]);
	radius = extent.y * fabs(edges[2].z) + extent.z * fabs(edges[2].y);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis4(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[1], edges[0]);
	p[0] = ft_dot_vec3(axis, r_vertices[0]);
	p[1] = ft_dot_vec3(axis, r_vertices[1]);
	radius = extent.x * fabs(edges[0].z) + extent.z * fabs(edges[0].x);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis5(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[1], edges[1]);
	p[0] = ft_dot_vec3(axis, r_vertices[1]);
	p[1] = ft_dot_vec3(axis, r_vertices[2]);
	radius = extent.x * fabs(edges[1].z) + extent.z * fabs(edges[1].x);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis6(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[1], edges[2]);
	p[0] = ft_dot_vec3(axis, r_vertices[2]);
	p[1] = ft_dot_vec3(axis, r_vertices[0]);
	radius = extent.x * fabs(edges[2].z) + extent.z * fabs(edges[2].x);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis7(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[2], edges[0]);
	p[0] = ft_dot_vec3(axis, r_vertices[0]);
	p[1] = ft_dot_vec3(axis, r_vertices[1]);
	radius = extent.x * fabs(edges[0].y) + extent.y * fabs(edges[0].x);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis8(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[2], edges[1]);
	p[0] = ft_dot_vec3(axis, r_vertices[1]);
	p[1] = ft_dot_vec3(axis, r_vertices[2]);
	radius = extent.x * fabs(edges[1].y) + extent.y * fabs(edges[1].x);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}

bool	axis9(t_vec3 unit[3], t_vec3 edges[3], t_vec3 r_vertices[3],
		t_vec3 extent)
{
	t_vec3	axis;
	double	p[2];
	double	radius;

	axis = ft_cross_vec3(unit[2], edges[2]);
	p[0] = ft_dot_vec3(axis, r_vertices[2]);
	p[1] = ft_dot_vec3(axis, r_vertices[0]);
	radius = extent.x * fabs(edges[2].y) + extent.y * fabs(edges[2].x);
	if (fmin(p[0], p[1]) > radius || fmax(p[0], p[1]) < -radius)
		return (false);
	return (true);
}
