#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include <math.h>

static t_vector2d	sphere_mapping(t_sphere sphere, t_vector3d point,
		t_vector3d normal)
{
	t_vector2d		uv;
	const double	offset_x = 0;

	(void)sphere;
	(void)point;
	uv.x = 0.5 + (atan2(normal.z, -normal.x) / (2 * M_PI));
	uv.y = 0.5 + (asin(-normal.y) / M_PI);
	uv.x = fmod(uv.x + offset_x, 1.0f);
	return (uv);
}

static t_vector3d	get_reference_vector(t_vector3d normal)
{
	t_vector3d	r;

	if (ft_supf(fabs(normal.y), 0.9))
		r = ft_set_vector3d(0, 0, copysign(1, normal.y));
	else
		r = ft_set_vector3d(0, 1, 0);
	return (r);
}

static t_vector2d	cylinder_mapping(t_cylinder cylinder, t_vector3d normal)
{
	t_vector2d	uv;

	uv.x = 0.5 + (atan2(normal.z, -normal.x) / (2 * M_PI));
	uv.y = ;
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
	uv.x = fmod(uv.x, 1.0f);
	uv.y = fmod(uv.y, 1.0f);
	if (ft_inff(uv.x, 0))
		uv.x = 1 + uv.x;
	if (ft_inff(uv.y, 0))
		uv.y = 1 + uv.y;
	return (uv);
}

t_vector2d	uv_at_point(t_object object, t_vector3d point, t_vector3d normal)
{
	t_vector2d	uv;

	if (object.type == SPHERE)
		uv = sphere_mapping(*(t_sphere *)object.object_r, point, normal);
	else if (object.type == PLANE)
		uv = plane_mapping(*(t_plane *)object.object_r, point, normal);
	else
		return (ft_init_vector2d(0));
	return (uv);
}
