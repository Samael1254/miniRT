#include "minirt_defs_bonus.h"
#include "minirt_transform_bonus.h"

static void	transform_sphere(t_sphere *sphere, t_camera camera)
{
	sphere->pos = world_to_view(sphere->pos, camera);
}

static void	transform_plane(t_plane *plane, t_camera camera)
{
	plane->normal = world_to_view(plane->normal, camera);
	plane->point = world_to_view(plane->point, camera);
}

static void	transform_cylinder(t_cylinder *cylinder, t_camera camera)
{
	cylinder->pos = world_to_view(cylinder->pos, camera);
	cylinder->axis = world_to_view(cylinder->axis, camera);
}

void	transform_point_light(t_point_light *light, t_camera camera)
{
	light->pos = world_to_view(light->pos, camera);
}

void	transform_object(t_object *object, t_camera camera)
{
	if (object->type == SPHERE)
		transform_sphere((t_sphere *)object->object_r, camera);
	if (object->type == PLANE)
		transform_plane((t_plane *)object->object_r, camera);
	if (object->type == CYLINDER)
		transform_cylinder((t_cylinder *)object->object_r, camera);
}
