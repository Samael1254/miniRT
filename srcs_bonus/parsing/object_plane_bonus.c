#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_bonus.h"
#include <stdlib.h>

static t_plane	*get_plane_data(t_state *state, char **split, t_object *obj)
{
	t_plane	*pl;
	bool	has_error;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
	{
		free(obj);
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	pl->point = get_vector(split[1], &has_error);
	if (!has_error)
		pl->normal = get_vector(split[2], &has_error);
	if (!is_vector3d_in_range(pl->normal, -1, 1) || has_error == true
		|| !is_norm_vector_valid(pl->normal))
	{
		free(obj);
		free(pl);
		ft_free_strtab(split);
		error("wrong parameter", "plane normal vector should be normalized",
			state);
	}
	return (pl);
}

t_object	*object_plane(t_state *state, char **split)
{
	t_object	*obj;
	bool		has_error;

	if (!ft_check_error_line(split, 4))
		error("wrong object definition", "plane needs 4 parameters", state);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	obj->object_r = get_plane_data(state, split, obj);
	obj->type = PLANE;
	obj->color = get_color(split[3], &has_error);
	if (has_error == true)
	{
		free(obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error(NULL, "malloc failed or vector data invalid", state);
	}
	return (obj);
}
