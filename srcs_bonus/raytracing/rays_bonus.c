#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_raytracing_bonus.h"
#include <math.h>
#include <pthread.h>
#include <unistd.h>

static double	vertical_fov_2(double horizontal_fov_2)
{
	return (atan(((double)WIN_Y / (double)WIN_X) * tan(horizontal_fov_2)));
}

static void	thread_shoot_rays_utils(t_state *state, t_ivec2 *coords,
		t_vec2 *delta, t_vec2 *rotator)
{
	while (coords->x < WIN_X)
	{
		if (state->toggle_aa)
			supersampling(*rotator, *coords, *delta, state);
		else
			trace_ray(*rotator, *coords, state);
		rotator->y -= delta->y;
		coords->x++;
	}
}

static void	*thread_shoot_rays(void *arg)
{
	t_thread_data	*data;
	t_ivec2			coords;
	t_vec2			delta;
	t_vec2			rotator;

	data = (t_thread_data *)arg;
	delta.y = 2 * data->state->scene.camera.fov_2 / WIN_X;
	delta.x = 2 * vertical_fov_2(data->state->scene.camera.fov_2) / WIN_Y;
	coords.y = data->start_y;
	rotator.x = vertical_fov_2(data->state->scene.camera.fov_2) - delta.x
		* data->start_y;
	while (coords.y < data->end_y)
	{
		rotator.y = data->state->scene.camera.fov_2;
		coords.x = 0;
		thread_shoot_rays_utils(data->state, &coords, &delta, &rotator);
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
		if (pthread_create(&threads[i], NULL, thread_shoot_rays,
				&thread_data[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_cancel(threads[i]);
				pthread_join(threads[i], NULL);
			}
			error("pthread_create", "crash", state);
		}
		i++;
	}
	ft_join_threads(state, threads);
}
