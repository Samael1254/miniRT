#include "minirt.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static t_plane	get_plane_data(t_state *state, t_plane *pl, char **split)
{
	t_vector3d	point;
	t_vector3d	normal;
	t_vector3d	color;
	bool		error;

	error = false;
	point = get_vector(split[1], &error);
	normal = get_vector(split[2], &error);
	color = get_vector(split[3], &error);
	if (!is_vector3d_in_range(color, 0, 255) || !is_vector3d_in_range(normal, -1, 1)
		|| error == true)
	{
		free(pl);
		fatal_error("sphere", "plane data isn't valid", state);
	}
	return ((t_plane){point, normal, color});
}

t_object	*object_plane(t_state *state, char **split)
{
	t_object	*obj;
	t_plane		*pl;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		free(pl);
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	*pl = get_plane_data(state, pl, split);
	obj->object_r = pl;
	obj->type = PLANE;
	return (obj);
}
