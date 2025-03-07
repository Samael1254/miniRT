#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt.h"
#include <stdlib.h>

static t_cylinder	*get_cylinder_data(t_state *state, char **split)
{
	t_cylinder	*cy;
	bool		has_error;

	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
	{
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	has_error = false;
	cy->pos = get_vector(split[1], &has_error);
	cy->axis = get_vector(split[2], &has_error);
	if (!is_vector3d_in_range(cy->axis, -1, 1) || has_error == true)
	{
		free(cy);
		ft_free_strtab(split);
		error("wrong parameter", "cylinder axis vector should be normalized",
			state);
	}
	cy->diameter = ft_atod(split[3]);
	cy->height = ft_atod(split[4]);
	return (cy);
}

t_object	*object_cylinder(t_state *state, char **split)
{
	t_object	*obj;
	bool		has_error;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	obj->object_r = get_cylinder_data(state, split);
	obj->type = CYLINDER;
	obj->color = get_color(split[5], &has_error);
	if (has_error == true)
	{
		ft_free_strtab(split);
		error(NULL, "malloc failed", state);
	}
	return (obj);
}
