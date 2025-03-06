#include "ft_algebra.h"
#include "minirt_defs.h"
#include <math.h>

static double	vertical_fov_2(double horizontal_fov_2)
{
	return (atan((WIN_Y / WIN_X) * tan(horizontal_fov_2)));
}

static t_ray	init_ray(t_camera camera, t_vector2d rotator)
{
	t_ray	ray;

	ray.origin = camera.pos;
	ray.direction = ft_set_vector3d(0, 0, -1);
	ray.direction = ft_rotate_vector3d(ray.direction, rotator);
	return (ray);
}

void	init_rays(t_camera camera)
{
	t_vector2d	rotator;
	int			coords[2];
	int			angle_deltas[2];
	double		v_fov_2;

	v_fov_2 = vertical_fov_2(camera.fov_2);
	coords[0] = 0;
	rotator.y = v_fov_2;
	angle_deltas[0] = 2 * v_fov_2 / WIN_Y;
	angle_deltas[1] = 2 * camera.fov_2 / WIN_X;
	while (coords[0] < WIN_Y)
	{
		coords[1] = 0;
		rotator.x = camera.fov_2;
		while (coords[1] < WIN_X)
		{
			init_ray(camera, rotator);
			rotator.x -= angle_deltas[1];
		}
		rotator.y -= angle_deltas[0];
	}
}
