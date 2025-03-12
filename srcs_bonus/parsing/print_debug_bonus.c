#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include <stdio.h>

void	print_vector3d(t_vector3d vec)
{
	printf("%.5f,%.5f,%.5f", vec.x, vec.y, vec.z);
}

static void	print_color(t_color col)
{
	printf("%d,%d,%d", col.r, col.g, col.b);
}

static void	print_sphere(t_object object)
{
	t_sphere	sphere;

	sphere = *(t_sphere *)object.object_r;
	printf("- sp ");
	print_vector3d(sphere.pos);
	printf(" %2.f ", sphere.diameter);
	print_color(object.color);
	printf("\n");
}

static void	print_plane(t_object object)
{
	t_plane	plane;

	plane = *(t_plane *)object.object_r;
	printf("- pl ");
	print_vector3d(plane.point);
	printf(" ");
	print_vector3d(plane.normal);
	printf(" ");
	print_color(object.color);
	printf("\n");
}

static void	print_cylinder(t_object object)
{
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)object.object_r;
	printf("- cy ");
	print_vector3d(cylinder.pos);
	printf(" %2.f ", cylinder.diameter);
	printf("%2.f ", cylinder.height);
	print_color(object.color);
	printf("\n");
}

static void	print_point_light(t_point_light light)
{
	printf("- L ");
	print_vector3d(light.pos);
	printf(" %2.f ", light.brightness);
	print_color(light.color);
	printf("\n");
}

static void	print_ambiant_light(t_ambiant_light ambiant_light)
{
	printf("- A ");
	printf("%2.f ", ambiant_light.brightness);
	print_color(ambiant_light.color);
	printf("\n");
}

static void	print_camera(t_camera camera)
{
	printf("- C ");
	print_vector3d(camera.pos);
	printf(" ");
	print_vector3d(camera.dir);
	printf(" %2.f", ft_rad_to_deg(camera.fov_2 * 2));
	printf("\n");
}

void	print_scene(t_scene scene)
{
	t_object	*object;

	print_ambiant_light(scene.a_light);
	print_camera(scene.camera);
	print_point_light(scene.p_light);
	while (scene.objects)
	{
		object = (t_object *)scene.objects->data;
		if (object->type == SPHERE)
			print_sphere(*object);
		if (object->type == PLANE)
			print_plane(*object);
		if (object->type == CYLINDER)
			print_cylinder(*object);
		scene.objects = scene.objects->next;
	}
}
