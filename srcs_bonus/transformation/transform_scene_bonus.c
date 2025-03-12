#include "minirt_defs_bonus.h"
#include "minirt_transform_bonus.h"

void	transform_scene(t_scene *scene)
{
	t_object	*object;

	transform_point_light(&scene->p_light, scene->camera);
	while (scene->objects)
	{
		object = (t_object *)scene->objects->data;
		transform_object(object, scene->camera);
		scene->objects = scene->objects->next;
	}
}
