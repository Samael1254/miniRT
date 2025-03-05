#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

static t_object	*add_sphere(t_state *state, char **split)
{
	t_object	*obj;
	t_vector3d	pos;
	double		diameter;
	t_vector3d	color;
	t_sphere	*sp;

	sp = ft_calloc(1, sizeof(t_sphere));
	obj = ft_calloc(1, sizeof(t_object));
	if (!sp) // FIX: free 1 sur 2 en fonction de celui qui fail
	{
		ft_free_strtab(split);
		fatal_error(NULL, "as malloc failed", state);
	}
	pos = get_vector(split[1]);
	diameter = ft_atod(split[2]);
	color = get_vector(split[3]);
	ft_free_strtab(split);
	if (!is_vector3d_in_range(color, 0, 255))
		fatal_error("sphere", "sphere color isn't valid", state);
	sp = &(t_sphere){pos, diameter, color};
	obj->object_r = sp;
	obj->type = SPHERE;
	return (obj);
}

// TODO: revoir l'ajout a la list qui segfault
void	add_object_to_list(t_state *state, char **split)
{
	if (!ft_strncmp(split[0], "sp", 2))
		ft_list_push_back(&state->scene.objects, add_sphere(state, split));
}
