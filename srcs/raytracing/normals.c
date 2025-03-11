#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs.h"

static t_vector3d	sphere_normal(t_sphere sphere, t_vector3d point)
{
	return (ft_normalize_vector3d(ft_sub_vectors3d(point, sphere.pos)));
}

static t_vector3d	plane_normal(t_plane plane, t_vector3d ray_dir)
{
	if (ft_supf(ft_dot_vectors3d(plane.normal, ray_dir), 0))
		return (ft_scale_vector3d(-1, plane.normal));
	return (plane.normal);
}

static t_vector3d	cylinder_normal(t_cylinder cylinder, t_vector3d point)
{
	t_vector3d	pa;
	double		baba;
	double		h;
	t_vector3d	radial_vec;

	pa = ft_sub_vectors3d(point, cylinder.pos);
	baba = ft_dot_vectors3d(cylinder.axis, cylinder.axis);
	h = ft_dot_vectors3d(pa, cylinder.axis) / baba;
	radial_vec = ft_sub_vectors3d(pa, ft_scale_vector3d(h, cylinder.axis));
	return (ft_normalize_vector3d(ft_scale_vector3d(1.0 / (cylinder.diameter
					/ 2.0), radial_vec)));
}

t_vector3d	normal_at_point(t_object object, t_vector3d point,
		t_vector3d ray_dir)
{
	if (object.type == SPHERE)
		return (sphere_normal(*(t_sphere *)object.object_r, point));
	if (object.type == PLANE)
		return (plane_normal(*(t_plane *)object.object_r, ray_dir));
	if (object.type == CYLINDER)
		return (cylinder_normal(*(t_cylinder *)object.object_r, point));
	return (ft_init_vector3d(0));
}
