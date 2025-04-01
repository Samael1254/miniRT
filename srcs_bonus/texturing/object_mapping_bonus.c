#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include "minirt_mapping_bonus.h"
#include <math.h>

t_vec2	sphere_mapping(t_vec3 normal)
{
	t_vec2			uv;
	const double	offset_x = 0;

	uv.x = 0.5 + atan2(normal.z, -normal.x) / (M_PI * 2);
	uv.y = 0.5 + asin(-normal.y) / M_PI;
	uv.x = fmod(uv.x + offset_x, 1.0f);
	return (uv);
}

t_vec2	cylinder_mapping(t_cylinder cylinder, t_vec3 point, t_vec3 normal)
{
	t_vec2	uv;
	t_vec3	relp;
	t_vec3	tangent;
	t_vec3	bitangent;

	tangent = ft_normalize_vec3(ft_cross_vec3(get_ref_vec(cylinder.axis),
				cylinder.axis));
	bitangent = ft_normalize_vec3(ft_cross_vec3(cylinder.axis, tangent));
	relp = ft_sub_vec3(point, cylinder.pos);
	uv.x = 0.5 + atan2(ft_dot_vec3(normal, bitangent), ft_dot_vec3(normal,
				tangent)) / (2 * M_PI);
	uv.y = -ft_dot_vec3(cylinder.axis, relp) / (M_PI * cylinder.diameter);
	if (ft_are_vec3_col(normal, cylinder.axis))
	{
		uv.x = 0.5 + ft_dot_vec3(relp, tangent) / (M_PI * cylinder.diameter);
		uv.y = 0.5 - ft_dot_vec3(relp, bitangent) / (M_PI * cylinder.diameter);
	}
	return (clamp_uv(uv));
}

t_vec2	cone_mapping(t_cone cone, t_vec3 point, t_vec3 normal)
{
	t_vec2	uv;
	t_vec3	relp;
	t_vec3	tangent;
	t_vec3	bitangent;

	tangent = ft_normalize_vec3(ft_cross_vec3(get_ref_vec(cone.axis),
				cone.axis));
	bitangent = ft_normalize_vec3(ft_cross_vec3(cone.axis, tangent));
	relp = ft_sub_vec3(point, cone.pos);
	uv.x = 0.5 + atan2(ft_dot_vec3(normal, bitangent), ft_dot_vec3(normal,
				tangent)) / (2 * M_PI);
	uv.y = -ft_dot_vec3(cone.axis, relp) / (4 * M_PI);
	return (clamp_uv(uv));
}

t_vec2	plane_mapping(t_plane plane, t_vec3 point, t_vec3 normal)
{
	t_vec3	r;
	t_vec3	relp;
	t_vec2	uv;
	t_vec3	tangent;
	t_vec3	bitangent;

	r = get_ref_vec(normal);
	tangent = ft_normalize_vec3(ft_cross_vec3(r, normal));
	bitangent = ft_normalize_vec3(ft_cross_vec3(normal, tangent));
	relp = ft_sub_vec3(point, plane.point);
	uv.x = ft_dot_vec3(tangent, relp) / 32;
	uv.y = -ft_dot_vec3(bitangent, relp) / 32;
	return (clamp_uv(uv));
}

t_vec2	triangle_mapping(t_triangle triangle, t_vec3 point)
{
	t_vec2	uv;

	uv = interpolate_triangle_data2d(triangle.vertices, point, triangle.uvs);
	return (uv);
}
