#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"

static t_vector3d	sphere_normal(t_sphere sphere, t_vector3d point)
{
	return (ft_normalize_vector3d(ft_sub_vectors3d(point, sphere.pos)));
}

static t_vector3d	plane_normal(t_plane plane)
{
	return (plane.normal);
}

static t_vector3d	cone_normal(t_cone cone, t_vector3d point)
{
	t_vector3d	cp;
	t_vector3d	tan;

	cp = ft_sub_vectors3d(point, cone.pos);
	tan = ft_cross_vectors3d(cone.axis, cp);
	return (ft_normalize_vector3d(ft_cross_vectors3d(cp, tan)));
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
	if (ft_inff(h, 0))
		return (ft_normalize_vector3d(ft_scale_vector3d(-1.0, ba)));
	if (ft_supf(h, 1))
		return (ft_normalize_vector3d(ba));
	return (ft_normalize_vector3d(ft_scale_vector3d(1.0 / radius,
				ft_sub_vectors3d(pa, ft_scale_vector3d(h, ba)))));
}

t_vector3d	color_to_normal(t_color color)
{
	t_vector3d	normal;

	normal.x = -(double)color.r / 127.5 + 1;
	normal.y = -(double)color.g / 127.5 + 1;
	normal.z = -(double)color.b / 127.5 + 1;
	return (normal);
}

t_vector3d	blend_normal_map(t_vector2d uv, t_vector3d normal,
		t_material material)
{
	t_vector3d	new_normal;

	if (!material.img_normal.img)
		return (normal);
	new_normal = color_to_normal(get_pixel_color(material.img_normal, uv));
	(void)new_normal;
	return (ft_lerp3d(normal, new_normal, 0.5));
}

t_vector3d	normal_at_point(t_object object, t_intersection inter,
		t_vector3d ray_dir, t_state *state)
{
	t_vector3d	normal;

	if (object.type == SPHERE)
		normal = sphere_normal(*(t_sphere *)object.object_r, inter.point);
	else if (object.type == PLANE)
		normal = plane_normal(*(t_plane *)object.object_r);
	else if (object.type == CYLINDER)
		normal = cylinder_normal(*(t_cylinder *)object.object_r, inter.point);
	else if (object.type == CONE)
		normal = cone_normal(*(t_cone *)object.object_r, inter.point);
	else
		return (ft_init_vector3d(0));
	if (ft_supf(ft_dot_vectors3d(normal, ray_dir), 0))
		normal = ft_scale_vector3d(-1, normal);
	normal = blend_normal_map(inter.uv, normal,
			state->mats_tab[inter.index_mat]);
	(void)state;
	return (normal);
}
