#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>

static t_vector3d	color_to_normal(t_color color)
{
	t_vector3d	normal;

	normal.x = (double)color.r / 127.5 - 1;
	normal.y = (double)color.g / 127.5 - 1;
	normal.z = (double)color.b / 127.5 - 1;
	return (normal);
}

// static t_vector3d	get_reference_vector(t_vector3d normal)
// {
// 	t_vector3d	r;
//
// 	if (ft_supf(fabs(normal.y), 0.9))
// 	{
// 		if (ft_supf(fabs(normal.z), 0.9))
// 			r = ft_set_vector3d(0, 0, 1);
// 		else
// 			r = ft_set_vector3d(0, 1, 0);
// 	}
// 	else if (ft_supf(fabs(normal.x), 0.9))
// 		r = ft_set_vector3d(0, 1, 0);
// 	else
// 		r = ft_set_vector3d(1, 0, 0);
// 	return (r);
// }

static t_vector3d	tangent_to_world(t_vector3d normal_tx,
		t_vector3d normal_world)
{
	t_vector3d	r;
	t_vector3d	tangent;
	t_vector3d	bitangent;
	t_vector3d	new_normal;

	r = get_reference_vector(normal_world);
	tangent = ft_normalize_vector3d(ft_cross_vectors3d(r, normal_tx));
	bitangent = ft_normalize_vector3d(ft_cross_vectors3d(normal_tx, tangent));
	new_normal = ft_normalize_vector3d(ft_add_vectors3d(ft_add_vectors3d(ft_scale_vector3d(-(normal_tx.x),
						tangent), ft_scale_vector3d(-(normal_tx.y), bitangent)),
				ft_scale_vector3d(normal_tx.z, normal_world)));
	return (new_normal);
}

t_vector3d	blend_normal_map(t_vector2d uv, t_vector3d normal,
		t_material material)
{
	t_vector3d	normal_tx;

	if (!material.img_normal.img)
		return (normal);
	normal_tx = color_to_normal(get_pixel_color(material.img_normal, uv));
	return (tangent_to_world(normal_tx, normal));
}
