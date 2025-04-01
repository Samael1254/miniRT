#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>

static t_vec3	color_to_normal(t_color color)
{
	t_vec3	normal;

	normal.x = (double)color.r / 127.5 - 1;
	normal.y = (double)color.g / 127.5 - 1;
	normal.z = (double)color.b / 127.5 - 1;
	return (normal);
}

// static t_vec3	get_ref_vec(t_vec3 normal)
// {
// 	t_vec3	r;
//
// 	if (ft_supf(fabs(normal.y), 0.9))
// 	{
// 		if (ft_supf(fabs(normal.z), 0.9))
// 			r = ft_set_vec3(0, 0, 1);
// 		else
// 			r = ft_set_vec3(0, 1, 0);
// 	}
// 	else if (ft_supf(fabs(normal.x), 0.9))
// 		r = ft_set_vec3(0, 1, 0);
// 	else
// 		r = ft_set_vec3(1, 0, 0);
// 	return (r);
// }

static t_vec3	tangent_to_world(t_vec3 normal_tx,
		t_vec3 normal_world)
{
	t_vec3	r;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	new_normal;

	r = get_ref_vec(normal_world);
	tangent = ft_normalize_vec3(ft_cross_vec3(r, normal_tx));
	bitangent = ft_normalize_vec3(ft_cross_vec3(normal_tx, tangent));
	new_normal = ft_normalize_vec3(ft_add_vec3(ft_add_vec3(ft_scale_vec3(-(normal_tx.x),
						tangent), ft_scale_vec3(-(normal_tx.y), bitangent)),
				ft_scale_vec3(normal_tx.z, normal_world)));
	return (new_normal);
}

t_vec3	blend_normal_map(t_vec2 uv, t_vec3 normal,
		t_material material)
{
	t_vec3	normal_tx;

	if (!material.img_normal.img)
		return (normal);
	normal_tx = color_to_normal(get_pixel_color(material.img_normal, uv));
	return (tangent_to_world(normal_tx, normal));
}
