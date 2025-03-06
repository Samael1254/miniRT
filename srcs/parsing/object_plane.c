#include "minirt.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static t_plane	*get_plane_data(t_state *state, char **split)
{
	t_plane		*pl;
	bool		error;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	error = false;
	pl->point = get_vector(split[1], &error);
	pl->normal = get_vector(split[2], &error);
	if (!is_vector3d_in_range(pl->normal, -1, 1) || error == true)
	{
		free(pl);
		ft_free_strtab(split);
		fatal_error("sphere", "plane data isn't valid", state);
	}
	return (pl);
}

t_object	*object_plane(t_state *state, char **split)
{
	t_object	*obj;
	bool		error;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	obj->object_r = get_plane_data(state, split);
	obj->type = PLANE;
	obj->color = get_color(split[3], &error);
	if (error == true)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	return (obj);
}
