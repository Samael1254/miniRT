#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include <math.h>

static t_vector2d	sphere_mapping(t_sphere sphere, t_vector3d point)
{
	t_vector3d	cp;
	t_vector2d	uv;

	cp = ft_normalize_vector3d(ft_sub_vectors3d(point, sphere.pos));
	uv.x = 0.5 + (atan2(cp.z, -cp.x) / (2 * M_PI));
	uv.y = 0.5 + (asin(-cp.y) / M_PI);
	return (uv);
}

static t_vector2d	plane_mapping(t_plane plane, t_vector3d point)
{
	t_vector3d	relp;
	t_vector2d	uv;

	relp = ft_normalize_vector3d(ft_sub_vectors3d(point, plane.point));
	uv.x = relp.x;
	uv.y = relp.z;
	return (uv);
}

t_vector2d	uv_at_point(t_object object, t_vector3d point)
{
	t_vector2d	uv;

	if (object.type == SPHERE)
		uv = sphere_mapping(*(t_sphere *)object.object_r, point);
	else if (object.type == PLANE)
		uv = plane_mapping(*(t_plane *)object.object_r, point);
	else
		return (ft_init_vector2d(0));
	return (uv);
}
