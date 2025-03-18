#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_bonus.h"
#include <stdlib.h>

static t_cone	*get_cone_data(t_state *state, char **split, t_object *obj)
{
	t_cone	*cone;
	bool	has_error;

	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
	{
		free(obj);
		ft_free_strtab(split);
		error(NULL, "as malloc failed", state);
	}
	cone->pos = get_vector(split[1], &has_error);
	cone->axis = get_vector(split[2], &has_error);
	cone->slope = ft_deg_to_rad(ft_atod(split[3]));
	if (has_error == true)
	{
		free(cone);
		free(obj);
		ft_free_strtab(split);
		error("cone", "cone color isn't valid", state);
	}
	return (cone);
}

t_object	*object_cone(t_state *state, char **split)
{
	t_object	*obj;

	if (!ft_check_error_line(split, 5))
		error("wrong object definition", "cone needs 4 parameters", state);
	check_line(state, split, 5);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error(NULL, "as malloc failed", state);
	}
	obj->object_r = get_cone_data(state, split, obj);
	obj->type = CONE;
	obj->index_mat = ft_atoi(split[4]);
	if (obj->index_mat < 0 || obj->index_mat > state->len_mats_tab)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error("object_cone", "malloc failed or vector data invalid", state);
	}
	return (obj);
}
