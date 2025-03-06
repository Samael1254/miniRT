#include "minirt.h"
#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static t_cylinder	*get_cylinder_data(t_state *state, char **split)
{
	t_cylinder	*cy;
	bool		error;

	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	error = false;
	cy->pos = get_vector(split[1], &error);
	cy->axis = get_vector(split[2], &error);
	if (!is_vector3d_in_range(cy->axis, -1, 1) || error == true)
	{
		free(cy);
		ft_free_strtab(split);
		fatal_error("sphere", "cyane data isn't valid", state);
	}
	cy->diameter = ft_atod(split[3]);
	cy->height = ft_atod(split[4]);
	return (cy);
}

t_object	*object_cylinder(t_state *state, char **split)
{
	t_object	*obj;
	bool		error;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	obj->object_r = get_cylinder_data(state, split);
	obj->type = CYLINDER;
	obj->color = get_color(split[5], &error);
	if (error == true)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	return (obj);
}
