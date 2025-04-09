#include "minirt_defs_bonus.h"
#include <stdlib.h>

void	free_triangle_obj(t_object *object)
{
	if (object && object->type == TRIANGLE)
	{
		free(object->object_r);
		free(object);
	}
}

void	free_bvh_elem(void *data)
{
	t_bvh_elem	*elem;

	if (!data)
		return ;
	elem = (t_bvh_elem *)data;
	if (elem->triangles)
		free(elem->triangles);
	free(elem);
}

void	free_node(t_bntree *node)
{
	if (!node)
		return ;
	if (!node->data)
		free_bvh_elem(node->data);
	free(node);
}
