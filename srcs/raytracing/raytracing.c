#include "ft_algebra.h"
#include "minirt_defs.h"
#include <math.h>

static double	vertical_fov_2(double horizontal_fov)
{
	return (atan((WIN_Y / WIN_X) * tan(horizontal_fov / 2)));
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
	int			i;
	int			j;
	double		v_fov_2;

	v_fov_2 = vertical_fov_2(camera.fov);
	i = 0;
	rotator.y = v_fov_2;
	while (i < WIN_Y)
	{
		j = 0;
		rotator.x = camera.fov / 2;
		while (j < WIN_X)
		{
			init_ray(camera, rotator);
			rotator.x -= camera.fov / WIN_X;
		}
		rotator.y -= 2 * v_fov_2 / WIN_Y;
	}
}
