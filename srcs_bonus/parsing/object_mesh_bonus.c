#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_obj_parser.h"
#include "minirt_parsing_bonus.h"
#include <stdlib.h>

static void	transform_mesh(t_mesh *mesh, t_vec3 pos, double scale)
{
	int	i;

	i = 0;
	while (i < mesh->n_vertices)
	{
		mesh->vertices[i] = ft_scale_vec3(scale, mesh->vertices[i]);
		mesh->vertices[i] = ft_add_vec3(pos, mesh->vertices[i]);
		i++;
	}
}

t_object	*object_mesh(t_state *state, char **split)
{
	t_object	*obj;
	bool		has_error;

	if (!ft_check_error_line(split, 5))
		error("wrong object definition", "mesh needs 4 parameters", state);
	check_line(state, split + 1, 4);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		ft_free_strtab(split);
		error("malloc failed", "in object_mesh", state);
	}
	obj->object_r = parse_obj_file(split[1], state);
	obj->type = MESH;
	obj->index_mat = ft_atoi(split[4]);
	transform_mesh(obj->object_r, get_vector(split[2], &has_error),
		ft_atod(split[3]));
	if (obj->index_mat > state->len_mats_tab || has_error)
	{
		free_mesh((t_mesh *)obj->object_r);
		free(obj);
		ft_free_strtab(split);
		error("wrong material index", "mesh", state);
	}
	return (obj);
}
