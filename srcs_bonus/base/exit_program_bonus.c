#include "ft_list.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include "mlx.h"
#include <stdlib.h>

static void	free_scene(t_scene *scene_r)
{
	t_object	*object;
	t_list		*tmp;

	tmp = scene_r->objects;
	while (tmp)
	{
		object = (t_object *)tmp->data;
		free(object->object_r);
		tmp = tmp->next;
	}
	ft_list_clear(scene_r->objects, &free);
}

static void	free_mlx(t_state *state)
{
	if (!state->display)
		return ;
	if (state->win && state->img_data.img)
		mlx_destroy_image(state->display, state->img_data.img);
	if (state->win)
		mlx_destroy_window(state->display, state->win);
	mlx_destroy_display(state->display);
	free(state->display);
}

int	exit_program(t_state *state, int status)
{
	int	i;

	if (state)
	{
		i = 0;
		while (i < 3)
		{
			if (state->id_list[i])
				free(state->id_list[i]);
			i++;
		}
		free_mlx(state);
		free_scene(&state->scene);
	}
	exit(status);
}
