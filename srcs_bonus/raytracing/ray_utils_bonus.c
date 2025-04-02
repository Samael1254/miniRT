#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include <pthread.h>

void	ft_join_threads(t_state *state, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
		if (pthread_join(threads[i++], NULL) != 0)
			error("pthread_join", "crash", state);
}
