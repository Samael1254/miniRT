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
