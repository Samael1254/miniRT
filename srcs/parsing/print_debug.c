#include "ft_algebra.h"
#include "minirt_defs.h"
#include <stdio.h>

void	print_vector3d(t_vector3d vec)
{
	printf("%f,%f,%f", vec.x, vec.y, vec.z);
}

void	print_sphere(t_sphere sphere)
{
	printf("- sp ");
	print_vector3d(sphere.pos);
	printf(" %f ", sphere.diameter);
	print_vector3d(sphere.color);
	printf("\n");
}

void	print_plane(t_plane plane)
{
	printf("- pl ");
	print_vector3d(plane.point);
	printf(" ");
	print_vector3d(plane.normal);
	printf(" ");
	print_vector3d(plane.color);
	printf("\n");
}

void	print_cylinder(t_cylinder cylinder)
{
	printf("- cy ");
	print_vector3d(cylinder.pos);
	printf(" %f ", cylinder.diameter);
	printf("%f ", cylinder.height);
	print_vector3d(cylinder.color);
	printf("\n");
}

void	print_point_light(t_point_light light)
{
	printf("- L ");
	print_vector3d(light.pos);
	printf(" %f ", light.brightness);
	print_vector3d(light.color);
	printf("\n");
}

void	print_ambiant_light(t_ambiant_light ambiant_light)
{
	printf("- A ");
	printf("%f ", ambiant_light.intensity);
	print_vector3d(ambiant_light.color);
	printf("\n");
}

void	print_camera(t_camera camera)
{
	printf("- A ");
	print_vector3d(camera.pos);
	printf(" ");
	print_vector3d(camera.rot);
	printf(" %d", camera.fov);
	printf("\n");
}

void	print_scene(t_scene scene)
{
}
