#include "ft_algebra.h"

t_vec3	triangle_center(t_vec3 vertices[3])
{
	t_vec3	center;

	center.x = (vertices[0].x + vertices[1].x + vertices[2].x);
	center.y = (vertices[0].y + vertices[1].y + vertices[2].y);
	center.z = (vertices[0].z + vertices[1].z + vertices[2].z);
	return (ft_scale_vec3(1/3., center));
}
