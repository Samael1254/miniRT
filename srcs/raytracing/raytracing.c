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

static void	init_rays(t_camera camera, t_ray rays[WIN_Y][WIN_X])
{
	t_vector2d	rotator;
	t_ivector2d	coords;
	t_ivector2d	angle_deltas;
	double		v_fov_2;

	v_fov_2 = vertical_fov_2(camera.fov_2);
	coords.y = 0;
	rotator.y = v_fov_2;
	angle_deltas.y = 2 * v_fov_2 / WIN_Y;
	angle_deltas.x = 2 * camera.fov_2 / WIN_X;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		rotator.x = camera.fov_2;
		while (coords.x < WIN_X)
		{
			rays[coords.y][coords.x] = init_ray(camera, rotator);
			rotator.x -= angle_deltas.x;
		}
		rotator.y -= angle_deltas.y;
	}
}

void	ray_tracing(t_scene scene)
{
	t_ray		rays[WIN_Y][WIN_X];
	t_ivector2d	coords;

	init_rays(scene.camera, rays);
	coords = ft_set_ivector2d(0, 0);
}
