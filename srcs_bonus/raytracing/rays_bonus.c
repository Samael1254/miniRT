#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

static void	trace_ray(t_vector2d rotator, t_ivector2d coords, t_state *state)
{
	t_ray			ray;
	t_intersection	inter;

	ray = init_ray(state->scene.camera, rotator);
	inter = intersect_scene(ray, state);
	put_pixel(&state->img_data, coords, phong_illumination(state, inter, ray));
}

static void	*thread_shoot_rays(void *arg)
{
	t_thread_data	*data;
	t_ivector2d		coords;
	t_vector2d		delta;
	t_vector2d		rotator;

	data = (t_thread_data *)arg;
	delta.y = 2 * data->state->scene.camera.fov_2 / WIN_X;
	delta.x = 2 * vertical_fov_2(data->state->scene.camera.fov_2) / WIN_Y;
	coords.y = data->start_y;
	rotator.x = vertical_fov_2(data->state->scene.camera.fov_2)
		- delta.x * data->start_y;
	while (coords.y < data->end_y)
	{
		rotator.y = data->state->scene.camera.fov_2;
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			trace_ray(rotator, coords, data->state);
			rotator.y -= delta.y;
			coords.x++;
		}
		rotator.x -= delta.x;
		coords.y++;
	}
	return (NULL);
}

void	shoot_rays(t_state *state)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_data	thread_data[THREAD_COUNT];
	int				i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		thread_data[i].start_y = i * (WIN_Y / THREAD_COUNT);
		thread_data[i].end_y = (i + 1) * (WIN_Y / THREAD_COUNT);
		thread_data[i].state = state;
		pthread_create(&threads[i], NULL, thread_shoot_rays, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
		pthread_join(threads[i++], NULL);
}
