#include "minirt_defs.h"
#include "minirt_errors.h"
#include <stdio.h>

char *pp_filter_name(enum e_post_process id)
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
	return NULL;
}

bool check_command_size(int size, int max_size)
{
	if (size > max_size)
		return (false);
	return (true);
}

enum e_cmd_status cmd_help(const char *text, int cmd_len)
{
	if (cmd_len > 2)
		return (warning("too many arguments", "no argument expected after 'help'"), CS_FAIL);
	printf("%s", text);
	return (CS_OK);
}
