#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

static t_sphere	get_sphere_data(t_state *state, t_sphere *sp, char **split)
{
	t_vector3d	pos;
	double		diameter;
	t_vector3d	color;
	bool		error;

	error = false;
	pos = get_vector(split[1], &error);
	diameter = ft_atod(split[2]);
	color = get_vector(split[3], &error);
	if (!is_vector3d_in_range(color, 0, 255) || error == true)
	{
		free(sp);
		fatal_error("sphere", "sphere color isn't valid", state);
	}
	return ((t_sphere){pos, diameter, color});
}

t_object	*object_sphere(t_state *state, char **split)
{
	t_object	*obj;
	t_sphere	*sp;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		free(sp);
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	*sp = get_sphere_data(state, sp, split);
	obj->object_r = sp;
	obj->type = SPHERE;
	return (obj);
}
