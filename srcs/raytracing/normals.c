#include "ft_algebra.h"
#include "minirt_defs.h"

static t_vector3d	sphere_normal(t_sphere sphere, t_vector3d point)
{
	return (ft_normalize_vector3d(ft_sub_vectors3d(point, sphere.pos)));
}

static t_vector3d	plane_normal(t_plane plane)
{
	return (plane.normal);
}

static t_vector3d	cylinder_normal(t_cylinder cylinder, t_vector3d point)
{
	t_vector3d	ba;
	t_vector3d	pa;
	double		h;
	double		radius;
	t_vector3d	a;

	radius = cylinder.diameter / 2.0;
	ba = ft_scale_vector3d(cylinder.height,
			ft_normalize_vector3d(cylinder.axis));
	a = ft_sub_vectors3d(cylinder.pos, ft_scale_vector3d(0.5, ba));
	pa = ft_sub_vectors3d(point, a);
	h = ft_dot_vectors3d(pa, ba) / ft_dot_vectors3d(ba, ba);
	if (h < 0.001)
		return (ft_normalize_vector3d(ft_scale_vector3d(-1.0, ba)));
	if (h > 0.999)
		return (ft_normalize_vector3d(ba));
	return (ft_normalize_vector3d(ft_scale_vector3d(1.0 / radius,
				ft_sub_vectors3d(pa, ft_scale_vector3d(h, ba)))));
}

t_vector3d	normal_at_point(t_object object, t_vector3d point)
{
	if (object.type == SPHERE)
		return (sphere_normal(*(t_sphere *)object.object_r, point));
	if (object.type == PLANE)
		return (plane_normal(*(t_plane *)object.object_r));
	if (object.type == CYLINDER)
		return (cylinder_normal(*(t_cylinder *)object.object_r, point));
	return (ft_init_vector3d(0));
}
