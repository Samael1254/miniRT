#include "ft_algebra.h"
#include "ft_memory.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

static void	init_rays(t_camera camera, t_ray **rays)
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

static t_ray	**alloc_rays(void)
{
	t_ray	**rays;
	int		i;

	rays = ft_calloc(WIN_Y, sizeof(t_ray *));
	if (!rays)
		return (NULL);
	i = 0;
	while (i < WIN_Y)
	{
		rays[i] = ft_calloc(WIN_X, sizeof(t_ray));
		if (!rays[i])
		{
			while (i > 0)
				free(rays[--i]);
			free(rays);
		}
		i++;
	}
	return (rays);
}

static void	free_rays(t_ray **rays)
{
	int	i;

	i = 0;
	while (i < WIN_Y)
		free(rays[i++]);
	free(rays);
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
			intersect_scene(&rays[coords.y][coords.x], state->scene.objects);
			coords.x++;
		}
		coords.y++;
	}
}

void	ray_tracing(t_state *state)
{
	t_ray	**rays;

	rays = alloc_rays();
	info(NULL, "ray tracing...");
	init_rays(state->scene.camera, rays);
	shoot_rays(rays, state);
	info(NULL, "rendering...");
	render_scene(state, rays);
	free_rays(rays);
	info(NULL, "done, press ESC to close");
}
