#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_bonus.h"
#include "minirt_obj_parser.h"
#include <stdlib.h>

t_object	*object_mesh(t_state *state, char **split)
{
	t_object	*obj;

	if (!ft_check_error_line(split, 2))
		error("wrong object definition", "mesh needs 2 parameters", state);
	check_line(state, split, 2);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error("malloc failed", "in object_mesh", state);
	}
	obj->object_r = parse_obj_file(split[1], state);
	obj->type = MESH;
	obj->index_mat = ft_atoi(split[2]);
	if (obj->index_mat > state->len_mats_tab)
	{
		free_mesh((t_mesh *)obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error("wrong material index", "mesh", state);
	}
	return (obj);
}
