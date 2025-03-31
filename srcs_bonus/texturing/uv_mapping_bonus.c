#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>

static t_vector2d	sphere_mapping(t_vector3d normal)
{
	t_vector2d		uv;
	const double	offset_x = 0;

	uv.x = 0.5 + atan2(normal.z, -normal.x) / (M_PI * 2);
	uv.y = 0.5 + asin(-normal.y) / M_PI;
	uv.x = fmod(uv.x + offset_x, 1.0f);
	return (uv);
}

static t_vector2d	cylinder_mapping(t_cylinder cylinder, t_vector3d point,
		t_vector3d normal)
{
	t_vector2d	uv;
	t_vector3d	relp;
	t_vector3d	tangent;
	t_vector3d	bitangent;

	tangent = ft_normalize_vector3d(ft_cross_vectors3d(get_reference_vector(cylinder.axis),
				cylinder.axis));
	bitangent = ft_normalize_vector3d(ft_cross_vectors3d(cylinder.axis,
				tangent));
	relp = ft_sub_vectors3d(point, cylinder.pos);
	uv.x = 0.5 + atan2(ft_dot_vectors3d(normal, bitangent),
			ft_dot_vectors3d(normal, tangent)) / (2 * M_PI);
	uv.y = -ft_dot_vectors3d(cylinder.axis, relp) / (M_PI * cylinder.diameter);
	if (ft_are_vectors3d_col(normal, cylinder.axis))
	{
		uv.x = 0.5 + ft_dot_vectors3d(relp, tangent) / (M_PI
				* cylinder.diameter);
		uv.y = 0.5 - ft_dot_vectors3d(relp, bitangent) / (M_PI
				* cylinder.diameter);
	}
	return (clamp_uv(uv));
}

static t_vector2d	cone_mapping(t_cone cone, t_vector3d point,
		t_vector3d normal)
{
	t_vector2d	uv;
	t_vector3d	relp;
	t_vector3d	tangent;
	t_vector3d	bitangent;

	tangent = ft_normalize_vector3d(ft_cross_vectors3d(get_reference_vector(cone.axis),
				cone.axis));
	bitangent = ft_normalize_vector3d(ft_cross_vectors3d(cone.axis, tangent));
	relp = ft_sub_vectors3d(point, cone.pos);
	uv.x = 0.5 + atan2(ft_dot_vectors3d(normal, bitangent),
			ft_dot_vectors3d(normal, tangent)) / (2 * M_PI);
	uv.y = -ft_dot_vectors3d(cone.axis, relp) / (4 * M_PI);
	return (clamp_uv(uv));
}

static t_vector2d	plane_mapping(t_plane plane, t_vector3d point,
		t_vector3d normal)
{
	t_vector3d	r;
	t_vector3d	relp;
	t_vector2d	uv;
	t_vector3d	tangent;
	t_vector3d	bitangent;

	r = get_reference_vector(normal);
	tangent = ft_normalize_vector3d(ft_cross_vectors3d(r, normal));
	bitangent = ft_normalize_vector3d(ft_cross_vectors3d(normal, tangent));
	relp = ft_sub_vectors3d(point, plane.point);
	uv.x = ft_dot_vectors3d(tangent, relp) / 32;
	uv.y = -ft_dot_vectors3d(bitangent, relp) / 32;
	return (clamp_uv(uv));
}

t_vector2d	triangle_mapping(t_triangle triangle, t_vector3d point)
{
	t_vector2d	uv;
	t_vector3d	vertices[3];
	t_vector2d	uvs[3];
	int			i;

	i = 0;
	while (i < 3)
	{
		vertices[i] = triangle.mesh->vertices[triangle.vertices[i]];
		uvs[i] = triangle.mesh->uvs[triangle.uvs[i]];
		i++;
	}
	uv = interpolate_triangle_data2d(vertices, point, uvs);
	return (uv);
}

t_vector2d	uv_at_point(t_object object, t_vector3d point, t_vector3d normal)
{
	t_vector2d	uv;

	if (object.type == SPHERE)
		uv = sphere_mapping(normal);
	else if (object.type == PLANE)
		uv = plane_mapping(*(t_plane *)object.object_r, point, normal);
	else if (object.type == CYLINDER)
		uv = cylinder_mapping(*(t_cylinder *)object.object_r, point, normal);
	else if (object.type == CONE)
		uv = cone_mapping(*(t_cone *)object.object_r, point, normal);
	// else if (object.type == TRIANGLE)
	// 	uv = triangle_mapping(*(t_triangle *)object.object_r, point);
	else
		return (ft_init_vector2d(0));
	return (uv);
}
