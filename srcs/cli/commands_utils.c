#include "minirt_defs.h"

char	*pp_filter_name(enum e_post_process id)
{
	switch (id)
	{
	case PP_NONE:
		return ("None");
	case PP_GAMMA:
		return ("Gamma correction");
	case PP_NEGATIVE:
		return ("Negative");
	case PP_VIGNETTE:
		return ("Vignette");
	case PP_SEPIA:
		return ("Sepia");
	case PP_GRAY:
		return ("Grayscale");
	case PP_POSTER:
		return ("Poster");
	case PP_SCANLINES:
		return ("Scanlines");
	case PP_BLACKWHITE:
		return ("Black and white");
	case PP_SATURATION:
		return ("High saturation");
	case PP_DARK:
		return ("Dark");
	}
}

bool	check_command_size(int size, int max_size)
{
	if (size > max_size)
		return (false);
	return (true);
}
