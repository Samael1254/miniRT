#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <math.h>
#include <stddef.h>

static t_intersection	make_intersection(t_ray ray, t_object *object,
		double distance_min)
{
	t_intersection	inter;

	if (!ft_in_rangef(distance_min, RAY_REACH_MIN, RAY_REACH_MAX))
	{
		inter.color = get_sky_color(ray);
		inter.point = ft_init_vector3d(INFINITY);
		inter.normal = ft_init_vector3d(0);
		return (inter);
	}
	inter.color = object->color;
	inter.point = ft_add_vectors3d(ray.origin, ft_scale_vector3d(distance_min,
				ray.direction));
	inter.normal = normal_at_point(*object, inter.point, ray.direction);
	return (inter);
}

static double	intersect_object(t_ray ray, t_object object)
{
	if (object.type == SPHERE)
		return (intersect_sphere(ray, *(t_sphere *)object.object_r));
	if (object.type == PLANE)
		return (intersect_plane(ray, *(t_plane *)object.object_r));
	if (object.type == CYLINDER)
		return (intersect_cylinder(ray, *(t_cylinder *)object.object_r));
	warning("invalid object", "object type not found");
	return (INFINITY);
}

t_intersection	intersect_scene(t_ray ray, t_list *objects)
{
	double		cur_distance;
	double		distance_min;
	t_object	*cur_object;
	t_object	*closest_object;

	distance_min = INFINITY;
	closest_object = NULL;
	while (objects)
	{
		cur_object = (t_object *)objects->data;
		cur_distance = intersect_object(ray, *cur_object);
		if (ft_in_rangef(cur_distance, RAY_REACH_MIN, distance_min))
		{
			distance_min = cur_distance;
			closest_object = cur_object;
		}
		objects = objects->next;
	}
	return (make_intersection(ray, closest_object, distance_min));
}
