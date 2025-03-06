#include "minirt_defs.h"
#include <math.h>

int	vertical_fov(int horizontal_fov)
{
	double	h_fov_rad;
	double	v_fov_rad;

	h_fov_rad = ft_deg_to_rad((double)horizontal_fov);
	v_fov_rad = 2 * atan((WIN_Y / WIN_X) * tan(h_fov_rad / 2));
	return (ft_rad_to_deg(v_fov_rad));
}

t_ray	init_ray(t_camera camera, int i, int j)
{
	t_ray	ray;

	ray.origin = camera.pos;
}
