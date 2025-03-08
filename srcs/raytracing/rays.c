#include "ft_algebra.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <math.h>
#include <stdio.h>

static double	vertical_fov_2(double horizontal_fov_2)
{
	return (atan(((double)WIN_Y / (double)WIN_X) * tan(horizontal_fov_2)));
}

static t_ray	init_ray(t_camera camera, t_vector2d rotator)
{
	t_ray		ray;
	t_vector3d	camera_x;
	t_vector3d	camera_y;
	double		m_rot_x[4][4];
	double		m_rot_y[4][4];

	camera_x = ft_cross_vectors3d(camera.dir, ft_set_vector3d(0, 1, 0));
	camera_y = ft_cross_vectors3d(camera_x, camera.dir);
	ft_set_rotation_matrix4d(m_rot_x, rotator.x, camera_x);
	ft_set_rotation_matrix4d(m_rot_y, rotator.y, camera_y);
	ft_add_matrixes4d(m_rot_x, m_rot_y, m_rot_x);
	ray.direction = ft_4dto3d_vector(ft_matrix_vector_product4d(m_rot_y,
				ft_matrix_vector_product4d(m_rot_x,
					ft_3dto4d_vector(camera.dir))));
	ray.origin = camera.pos;
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
