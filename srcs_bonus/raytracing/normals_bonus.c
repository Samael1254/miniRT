#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"

static t_vec3	sphere_normal(t_sphere sphere, t_vec3 point)
{
	return (ft_normalize_vec3(ft_sub_vec3(point, sphere.pos)));
}

static t_vec3	plane_normal(t_plane plane)
{
	return (plane.normal);
}

static t_vec3	cone_normal(t_cone cone, t_vec3 point)
{
	t_vec3	cp;
	t_vec3	tan;

	cp = ft_sub_vec3(point, cone.pos);
	tan = ft_cross_vec3(cone.axis, cp);
	return (ft_normalize_vec3(ft_cross_vec3(cp, tan)));
}

static t_vec3	triangle_normal(t_triangle triangle, t_vec3 point)
{
	t_vec3	normal;

	normal = interpolate_triangle_data3d(triangle.vertices, point,
			triangle.normals);
	return (normal);
}

static t_vec3	cylinder_normal(t_cylinder cylinder, t_vec3 point)
{
	t_vec3	ba;
	t_vec3	pa;
	double		h;
	double		radius;
	t_vec3	a;

	radius = cylinder.diameter / 2.0;
	ba = ft_scale_vec3(cylinder.height,
			ft_normalize_vec3(cylinder.axis));
	a = ft_sub_vec3(cylinder.pos, ft_scale_vec3(0.5, ba));
	pa = ft_sub_vec3(point, a);
	h = ft_dot_vec3(pa, ba) / ft_dot_vec3(ba, ba);
	if (ft_inff(h, 0))
		return (ft_normalize_vec3(ft_scale_vec3(-1.0, ba)));
	if (ft_supf(h, 1))
		return (ft_normalize_vec3(ba));
	return (ft_normalize_vec3(ft_scale_vec3(1.0 / radius,
				ft_sub_vec3(pa, ft_scale_vec3(h, ba)))));
}

t_vec3	normal_at_point(t_object object, t_intersection inter,
		t_vec3 ray_dir)
{
	t_vec3	normal;

	if (object.type == SPHERE)
		normal = sphere_normal(*(t_sphere *)object.object_r, inter.point);
	else if (object.type == PLANE)
		normal = plane_normal(*(t_plane *)object.object_r);
	else if (object.type == CYLINDER)
		normal = cylinder_normal(*(t_cylinder *)object.object_r, inter.point);
	else if (object.type == CONE)
		normal = cone_normal(*(t_cone *)object.object_r, inter.point);
	else if (object.type == TRIANGLE)
		normal = triangle_normal(*(t_triangle *)object.object_r, inter.point);
	else
		return (ft_init_vec3(0));
	if (ft_supf(ft_dot_vec3(normal, ray_dir), 0))
		normal = ft_scale_vec3(-1, normal);
	return (normal);
}
