#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

// TODO: revoir l'ajout a la list qui segfault
void	add_object_to_list(t_state *state, char **split)
{
	t_object	*obj;

	obj = NULL;
	if (!ft_strncmp(split[0], "sp", 2))
		obj = object_sphere(state, split);
	if (!ft_strncmp(split[0], "pl", 2))
		obj = object_sphere(state, split);
	if (obj)
		ft_list_push_back(&state->scene.objects, obj);
}
