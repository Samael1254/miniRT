#include "ft_algebra.h"
#include "minirt_defs_bonus.h"

t_vec3	world_to_view(t_vec3 vect, t_camera camera)
{
	t_vec4	view_vect;
	t_vec3	i_z_axis;
	double		m[4][4];

	i_z_axis = ft_set_vec3(0, 0, -1);
	view_vect = ft_translate_vec4(ft_3dto4d_vector(vect),
			ft_scale_vec3(-1, camera.pos));
	view_vect = ft_rotate_vec4(view_vect, ft_scale_vec3(-1,
				camera.dir));
	ft_set_rotation_mat4(m, ft_vec3_angle(camera.dir, i_z_axis),
		ft_cross_vec3(camera.dir, i_z_axis));
	view_vect = ft_mat_vec_product4(m, view_vect);
	return (ft_4dto3d_vector(view_vect));
}
