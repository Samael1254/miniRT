#include "minirt_defs.h"

t_vector3d	world_to_view(t_vector3d vect, t_camera camera)
{
	t_vector4d	view_vect;

	view_vect = ft_translate_vector4d(ft_3dto4d_vector(vect),
			ft_scale_vector3d(-1, camera.pos));
	view_vect = ft_rotate_vector4d(view_vect, ft_scale_vector3d(-1,
				camera.rot));
	return (ft_4dto3d_vector(view_vect));
}
