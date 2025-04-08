#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stdbool.h>

static t_vec3	ft_abs_vec3(t_vec3 v)
{
	t_vec3	u;

	u.x = fabs(v.x);
	u.y = fabs(v.y);
	u.z = fabs(v.z);
	return (u);
}

bool	aabb_aabb_overlap(t_aabb a, t_aabb b)
{
	if (a.min.x > b.max.x || a.max.x < b.min.x)
		return (false);
	if (a.min.y > b.max.y || a.max.y < b.min.y)
		return (false);
	if (a.min.z > b.max.z || a.max.z < b.min.z)
		return (false);
	return (true);
}

static t_vec3	aabb_center(t_aabb box)
{
	return (ft_scale_vec3(0.5, ft_add_vec3(box.min, box.max)));
}

bool	plane_aabb_overlap(t_vec3 p_normal, t_vec3 p_point, t_aabb box)
{
	t_vec3	c;
	t_vec3	h;
	double	r;
	double	s;

	c = aabb_center(box);
	h = ft_sub_vec3(box.max, c);
	r = ft_dot_vec3(h, ft_abs_vec3(p_normal));
	s = ft_dot_vec3(p_normal, c) - ft_dot_vec3(p_normal, p_point);
	return (fabs(s) <= r);
}

bool	test3(t_vec3 r_vertices[3], t_vec3 edges[3], t_vec3 extent,
		t_vec3 unit[3])
{
	double	radius;
	t_vec3	axes[9];
	double	p[3];
	int		i;
	int		j;

	axes[0] = ft_cross_vec3(unit[0], edges[0]);
	axes[1] = ft_cross_vec3(unit[0], edges[1]);
	axes[2] = ft_cross_vec3(unit[0], edges[2]);
	axes[3] = ft_cross_vec3(unit[1], edges[0]);
	axes[4] = ft_cross_vec3(unit[1], edges[1]);
	axes[5] = ft_cross_vec3(unit[1], edges[2]);
	axes[6] = ft_cross_vec3(unit[2], edges[0]);
	axes[7] = ft_cross_vec3(unit[2], edges[1]);
	axes[8] = ft_cross_vec3(unit[2], edges[2]);
	i = -1;
	while (++i < 9)
	{
		if (ft_vec3_norm(axes[i]) < 1e-5)
			continue ;
		radius = ft_dot_vec3(extent, ft_abs_vec3(axes[i]));
		j = -1;
		while (++j < 3)
			p[j] = ft_dot_vec3(axes[i], r_vertices[j]);
		if (fmin(p[0], fmin(p[1], p[2])) > radius || fmax(p[0], fmax(p[1],
					p[2])) < -radius)
			return (false);
	}
	return (true);
}

// bool	test3(t_vec3 r_vertices[3], t_vec3 edges[3], t_vec3 extent,
// 		t_vec3 unit[3])
// {
// 	if (!axis1(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis2(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis3(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis4(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis5(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis6(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis7(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis8(unit, edges, r_vertices, extent))
// 		return (false);
// 	if (!axis9(unit, edges, r_vertices, extent))
// 		return (false);
// 	return (true);
// }

t_aabb	create_triangle_aabb(const t_vec3 vertices[3])
{
	unsigned int	i;
	t_aabb			aabb;
	const double	epsilon = 1e-5;

	i = 0;
	aabb.min = ft_init_vec3(INFINITY);
	aabb.max = ft_init_vec3(-INFINITY);
	while (i < 3)
	{
		aabb.min.x = fmin(aabb.min.x, vertices[i].x);
		aabb.min.y = fmin(aabb.min.y, vertices[i].y);
		aabb.min.z = fmin(aabb.min.z, vertices[i].z);
		aabb.max.x = fmax(aabb.max.x, vertices[i].x);
		aabb.max.y = fmax(aabb.max.y, vertices[i].y);
		aabb.max.z = fmax(aabb.max.z, vertices[i].z);
		i++;
	}
	aabb.min = ft_sub_vec3(aabb.min, ft_init_vec3(epsilon));
	aabb.max = ft_add_vec3(aabb.max, ft_init_vec3(epsilon));
	return (aabb);
}

bool	triangle_aabb_overlap(const unsigned int vertices_id[3], t_aabb box,
		const t_vec3 *vertices)
{
	t_vec3	unit[3];
	t_vec3	t_vertices[3];
	t_vec3	r_vertices[3];
	t_vec3	edges[3];
	t_vec3	center;
	t_vec3	extent;

	center = aabb_center(box);
	extent = ft_sub_vec3(box.max, center);
	t_vertices[0] = vertices[vertices_id[0]];
	t_vertices[1] = vertices[vertices_id[1]];
	t_vertices[2] = vertices[vertices_id[2]];
	r_vertices[0] = ft_sub_vec3(t_vertices[0], center);
	r_vertices[1] = ft_sub_vec3(t_vertices[1], center);
	r_vertices[2] = ft_sub_vec3(t_vertices[2], center);
	edges[0] = ft_sub_vec3(r_vertices[1], r_vertices[0]);
	edges[1] = ft_sub_vec3(r_vertices[2], r_vertices[1]);
	edges[2] = ft_sub_vec3(r_vertices[0], r_vertices[2]);
	unit[0] = ft_set_vec3(1, 0, 0);
	unit[1] = ft_set_vec3(0, 1, 0);
	unit[2] = ft_set_vec3(0, 0, 1);
	if (!test3(r_vertices, edges, extent, unit))
		return (false);
	if (!aabb_aabb_overlap(box, create_triangle_aabb(t_vertices)))
		return (false);
	if (!plane_aabb_overlap(ft_normalize_vec3(ft_cross_vec3(edges[0],
					edges[1])), t_vertices[0], box))
		return (false);
	return (true);
}
