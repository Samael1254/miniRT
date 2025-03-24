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

void	shoot_rays(t_state *state)
{
	t_ivector2d		coords;
	t_intersection	inter;
	t_vector2d		angle_deltas;
	double			v_fov_2;
	t_vector2d		rotator;
	t_ray			ray;

	v_fov_2 = vertical_fov_2(state->scene.camera.fov_2);
	angle_deltas.y = 2 * state->scene.camera.fov_2 / WIN_X;
	angle_deltas.x = 2 * v_fov_2 / WIN_Y;
	rotator.x = v_fov_2;
	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		rotator.y = state->scene.camera.fov_2;
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			ray = init_ray(state->scene.camera, rotator);
			inter = intersect_scene(ray, state);
			put_pixel(&state->img_data, coords, phong_illumination(state, inter,
					ray));
			rotator.y -= angle_deltas.y;
			coords.x++;
		}
		rotator.x -= angle_deltas.x;
		coords.y++;
	}
}
