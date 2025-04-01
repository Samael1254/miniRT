#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include <sys/time.h>
#include <unistd.h>

struct timeval	get_time(t_state *state)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error(NULL, "gettimofday failed", state);
	return (time);
}

long	get_time_diff(struct timeval time, struct timeval start_time)
{
	time_t		s;
	suseconds_t	us;

	s = time.tv_sec - start_time.tv_sec;
	us = time.tv_usec - start_time.tv_usec;
	return (s * 1000 + us / 1000);
}
