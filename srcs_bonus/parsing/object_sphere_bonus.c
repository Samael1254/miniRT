#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_bonus.h"
#include <stdio.h>
#include <stdlib.h>

static t_sphere	*get_sphere_data(t_state *state, char **split, t_object *obj)
{
	t_sphere	*sp;
	bool		has_error;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
	{
		free(obj);
		ft_free_strtab(split);
		error(NULL, "as malloc failed", state);
	}
	sp->pos = get_vector(split[1], &has_error);
	sp->diameter = ft_atod(split[2]);
	if (has_error == true)
	{
		free(sp);
		free(obj);
		ft_free_strtab(split);
		error("sphere", "sphere color isn't valid", state);
	}
	return (sp);
}

t_object	*object_sphere(t_state *state, char **split)
{
	t_object	*obj;

	if (!ft_check_error_line(split, 4))
		error("wrong object definition", "sphere needs 4 parameters", state);
	check_line(state, split, 4);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error(NULL, "as malloc failed", state);
	}
	obj->object_r = get_sphere_data(state, split, obj);
	obj->type = SPHERE;
	obj->index_mat = ft_atoi(split[3]);
	if (obj->index_mat < 0 || obj->index_mat > state->len_mats_tab)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error(NULL, "malloc failed or vector data invalid", state);
	}
	return (obj);
}
