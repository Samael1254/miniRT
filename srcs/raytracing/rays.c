#include "ft_algebra.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>

static double	vertical_fov_2(double horizontal_fov_2)
{
	return (atan(((double)WIN_Y / (double)WIN_X) * tan(horizontal_fov_2)));
}

static t_ray	init_ray(t_camera camera, t_vector2d rotator)
{
	t_ray	ray;

	ray.origin = camera.pos;
	ray.direction = camera.dir;
	ray.direction = ft_scale_vector3d(1, ft_rotate_vector3d(ray.direction,
				rotator));
	ray.color.r = 0;
	ray.color.g = 0;
	ray.color.b = 0;
	return (ray);
}

void	init_rays(t_camera camera, t_ray **rays)
{
	t_vector2d	rotator;
	t_ivector2d	coords;
	t_vector2d	angle_deltas;
	double		v_fov_2;

	v_fov_2 = vertical_fov_2(camera.fov_2);
	coords.y = 0;
	rotator.x = -v_fov_2;
	angle_deltas.y = 2 * camera.fov_2 / WIN_X;
	angle_deltas.x = 2 * v_fov_2 / WIN_Y;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		rotator.y = camera.fov_2;
		while (coords.x < WIN_X)
		{
			rays[coords.y][coords.x] = init_ray(camera, rotator);
			rotator.y -= angle_deltas.y;
			coords.x++;
		}
		rotator.x += angle_deltas.x;
		coords.y++;
	}
}

void	shoot_rays(t_ray **rays, t_state *state)
{
	t_ivector2d	coords;

	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			rays[coords.y][coords.x] = intersect_scene(rays[coords.y][coords.x],
					state->scene.objects);
			coords.x++;
		}
		coords.y++;
	}
}
