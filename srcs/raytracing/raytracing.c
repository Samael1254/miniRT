#include "ft_algebra.h"
#include "minirt.h"
#include "minirt_defs.h"
#include "mlx.h"
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
			coords.x++;
		}
		rotator.y -= angle_deltas.y;
		coords.y++;
	}
}

void	ray_tracing(t_state *state)
{
	t_ray			rays[WIN_Y][WIN_X];
	t_ivector2d		coords;
	t_intersection	*inter;

	init_rays(state->scene.camera, rays);
	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			inter = intersect_scene(rays[coords.y][coords.x],
					state->scene.objects);
			put_pixel(&state->img_data, coords, inter->color);
			coords.x++;
		}
		coords.y++;
	}
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
}
