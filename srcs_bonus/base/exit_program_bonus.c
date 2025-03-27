#include "ft_list.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include "minirt_obj_parser.h"
#include "mlx.h"
#include <stdlib.h>

static void	free_materials(t_state *state)
{
	unsigned int	i;
	t_material		material;

	i = 0;
	while (i < state->len_mats_tab)
	{
		material = state->mats_tab[i++];
		if (material.img_texture.img)
			mlx_destroy_image(state->display, material.img_texture.img);
		if (material.img_normal.img)
			mlx_destroy_image(state->display, material.img_normal.img);
	}
	free(state->mats_tab);
}

static void	free_scene(t_scene *scene_r)
{
	t_object	*object;
	t_list		*tmp;

	tmp = scene_r->objects;
	while (tmp)
	{
		object = (t_object *)tmp->data;
		if (object->type == MESH)
			free_mesh((t_mesh *)object->object_r);
		else
			free(object->object_r);
		tmp = tmp->next;
	}
	ft_list_clear(scene_r->objects, &free);
	ft_list_clear(scene_r->lights, &free);
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
		free_materials(state);
		free_scene(&state->scene);
		free_mlx(state);
	}
	exit(status);
}
