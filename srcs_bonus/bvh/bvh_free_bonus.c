# include <stdlib.h>
# include "minirt_defs_bonus.h"

void	free_bvh_elem(t_bvh_elem *elem)
{
	if (!elem)
		return ;
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
