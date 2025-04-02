#ifndef MINIRT_RAYTRACING_BONUS_H
# define MINIRT_RAYTRACING_BONUS_H

# include "minirt_defs_bonus.h"
# include <pthread.h>

void	shoot_rays(t_state *state);
void	ray_tracing(t_state *state);
void	ft_join_threads(t_state *state, pthread_t *threads);

#endif
