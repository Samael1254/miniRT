#include "ft_algebra.h"
#include "minirt_obj_parser.h"
#include <stdio.h>

static void	print_vertex(t_vec3 vertex, const char *type)
{
	printf("%s %f %f %f\n", type, vertex.x, vertex.y, vertex.z);
}

static void	print_uv(t_vec2 uv, const char *type)
{
	printf("%s %f %f\n", type, uv.x, uv.y);
}

static void	print_face(const t_vertex *face)
{
	int	i;

	printf("f ");
	i = 0;
	while (i < 3)
	{
		printf("%d", face[i].geo_id);
		if (face[i].text_id != -1 || face[i].norm_id != -1)
			printf("/");
		if (face[i].text_id != -1)
			printf("%d", face[i].text_id);
		if (face[i].norm_id != -1)
			printf("/%d", face[i].norm_id);
		if (i != 2)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	print_mesh(t_mesh *mesh)
{
	int	i;

	i = 0;
	while (i < mesh->n_vertices)
		print_vertex(mesh->vertices[i++], "v");
	if (mesh->n_vertices > 0)
		printf("\n");
	i = 0;
	while (i < mesh->n_normals)
		print_vertex(mesh->normals[i++], "vn");
	if (mesh->n_normals > 0)
		printf("\n");
	i = 0;
	while (i < mesh->n_uvs)
		print_uv(mesh->uvs[i++], "vt");
	if (mesh->n_uvs > 0)
		printf("\n");
	i = 0;
	while (i < mesh->n_faces)
		print_face(mesh->faces[i++]);
}
