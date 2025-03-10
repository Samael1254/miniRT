#include "ft_algebra.h"
#include "minirt_defs.h"

t_vector3d	sphere_normal(t_sphere sphere, t_vector3d point)
{
	return (ft_sub_vectors3d(point, sphere.pos));
}

t_vector3d	cylinder_normal(t_cylinder cylinder, t_vector3d point)
{
	if (0)
	{
		if (0)
			return (cylinder.axis);
		return (ft_scale_vector3d(-1, cylinder.axis));
	}
}

t_vector3d	normal_at_point(t_object object, t_vector3d point)
{
	if (object.type == SPHERE)
		return (sphere_normal(*(t_sphere *)object.object_r, point));
	if (object.type == PLANE)
		return ((*(t_plane *)object.object_r).normal);
	if (object.type == CYLINDER)
		return (cylinder_normal(*(t_cylinder *)object.object_r, point));
	return (ft_init_vector3d(0));
}
