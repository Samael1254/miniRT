#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>

static double	vertical_fov_2(double horizontal_fov_2)
{
	return (atan(((double)WIN_Y / (double)WIN_X) * tan(horizontal_fov_2)));
}

static t_ray	init_ray(t_camera camera, t_vector2d rotator)
{
	t_ray	ray;
	double	m_rot_x[4][4];
	double	m_rot_y[4][4];

	ft_set_rotation_matrix4d(m_rot_x, rotator.x, camera.x_axis);
	ft_set_rotation_matrix4d(m_rot_y, rotator.y, camera.y_axis);
	ray.direction = ft_4dto3d_vector(ft_matrix_vector_product4d(m_rot_y,
				ft_matrix_vector_product4d(m_rot_x,
					ft_3dto4d_vector(camera.dir))));
	ray.origin = camera.pos;
	ray.color = init_color(0, 0, 0);
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
	rotator.x = v_fov_2;
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
		rotator.x -= angle_deltas.x;
		coords.y++;
	}
}

void	shoot_rays(t_ray **rays, t_state *state)
{
	t_ivector2d		coords;
	t_intersection	inter;

	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			inter = intersect_scene(rays[coords.y][coords.x],
					state->scene.objects);
			rays[coords.y][coords.x].color = phong_illumination(state, inter,
					rays[coords.y][coords.x]);
			coords.x++;
		}
		coords.y++;
	}
}
