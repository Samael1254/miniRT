#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

static t_sphere	*get_sphere_data(t_state *state, char **split)
{
	t_sphere	*sp;
	bool		error;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	sp->pos = get_vector(split[1], &error);
	sp->diameter = ft_atod(split[2]);
	if (error == true)
	{
		free(sp);
		ft_free_strtab(split);
		fatal_error("sphere", "sphere color isn't valid", state);
	}
	return (sp);
}

t_object	*object_sphere(t_state *state, char **split)
{
	t_object	*obj;
	bool		error;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	obj->object_r = get_sphere_data(state, split);
	obj->type = SPHERE;
	obj->color = get_color(split[3], &error);
	if (error == true)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	return (obj);
}
