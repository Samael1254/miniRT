#include "ft_algebra.h"
#include "minirt_defs.h"

t_vector3d	world_to_view(t_vector3d vect, t_camera camera)
{
	t_vector4d	view_vect;
	t_vector3d	i_z_axis;
	double		m[4][4];

	i_z_axis = ft_set_vector3d(0, 0, -1);
	view_vect = ft_translate_vector4d(ft_3dto4d_vector(vect),
			ft_scale_vector3d(-1, camera.pos));
	view_vect = ft_rotate_vector4d(view_vect, ft_scale_vector3d(-1,
				camera.dir));
	ft_set_rotation_matrix4d(m, ft_vectors3d_angle(camera.dir, i_z_axis),
		ft_cross_vectors3d(camera.dir, i_z_axis));
	view_vect = ft_matrix_vector_product4d(m, view_vect);
	return (ft_4dto3d_vector(view_vect));
}
