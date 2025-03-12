#ifndef MINIRT_TRANSFORM_H
# define MINIRT_TRANSFORM_H

# include "minirt_defs_bonus.h"

t_vector3d	world_to_view(t_vector3d vect, t_camera camera);
void		transform_point_light(t_point_light *light, t_camera camera);
void		transform_object(t_object *object, t_camera camera);

#endif
