#include "ft_strings.h"
#include "minirt_bonus.h"
#include <stdlib.h>

void	add_object_to_list(t_state *state, char **split)
{
	t_object	*obj;

	obj = NULL;
	if (!ft_strncmp(split[0], "sp", 2))
		obj = object_sphere(state, split);
	else if (!ft_strncmp(split[0], "pl", 2))
		obj = object_plane(state, split);
	else if (!ft_strncmp(split[0], "cy", 2))
		obj = object_cylinder(state, split);
	else if (!ft_strncmp(split[0], "co", 2))
		obj = object_cone(state, split);
	else if (!ft_strncmp(split[0], "mesh", 4))
		obj = object_mesh(state, split);
	if (obj)
		ft_list_push_back(&state->scene.objects, obj);
}
