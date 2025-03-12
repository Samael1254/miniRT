#include "ft_memory.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <stdlib.h>

static void	free_rays(t_ray **rays)
{
	int	i;

	i = 0;
	while (i < WIN_Y)
		free(rays[i++]);
	free(rays);
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
}
