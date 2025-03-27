#include "ft_algebra.h"
#include "ft_math.h"
#include <math.h>

t_vector3d	get_reference_vector(t_vector3d normal)
{
	t_vector3d	r;

	if (ft_supf(fabs(normal.y), 0.999))
		r = ft_set_vector3d(0, 0, copysign(1, normal.y));
	else
		r = ft_set_vector3d(0, 1, 0);
	return (r);
}

t_vector2d	clamp_uv(t_vector2d uv)
{
	uv.x = fmod(uv.x, 1.0f);
	uv.y = fmod(uv.y, 1.0f);
	if (ft_inff(uv.x, 0))
		uv.x = 1 + uv.x;
	if (ft_inff(uv.y, 0))
		uv.y = 1 + uv.y;
	return (uv);
}

static t_vector3d	cartesian_to_barycentric3d(t_vector3d vertices[3],
		t_vector3d point)
{
	t_vector3d	bary;
	double		areas[3];
	t_vector3d	edges[2];
	t_vector3d	vectors[3];

	edges[0] = ft_sub_vectors3d(vertices[1], vertices[0]);
	edges[1] = ft_sub_vectors3d(vertices[2], vertices[0]);
	vectors[0] = ft_sub_vectors3d(vertices[0], point);
	vectors[1] = ft_sub_vectors3d(vertices[1], point);
	vectors[2] = ft_sub_vectors3d(vertices[2], point);
	areas[0] = ft_vector3d_norm(ft_cross_vectors3d(edges[0], edges[1]));
	areas[1] = ft_vector3d_norm(ft_cross_vectors3d(vectors[1], vectors[2]));
	areas[0] = ft_vector3d_norm(ft_cross_vectors3d(vectors[2], vectors[0]));
	bary.x = areas[1] / areas[0];
	bary.y = areas[2] / areas[0];
	bary.z = 1 - bary.x - bary.y;
	return (bary);
}

t_vector3d	interpolate_triangle_data3d(t_vector3d vertices[3],
		t_vector3d point, t_vector3d data[3])
{
	t_vector3d	bary;
	t_vector3d	lerp;

	bary = cartesian_to_barycentric3d(vertices, point);
	lerp.x = bary.x * data[0].x + bary.y * data[1].x + bary.z * data[2].x;
	lerp.y = bary.x * data[0].y + bary.y * data[1].y + bary.z * data[2].y;
	lerp.z = bary.x * data[0].z + bary.y * data[1].z + bary.z * data[2].z;
	return (lerp);
}
