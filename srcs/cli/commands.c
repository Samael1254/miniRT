#include "minirt_defs.h"
#include "minirt_graphics.h"
#include <stdio.h>

enum e_cmd_status	keys_cmd(void)
{
	printf("-- Keybindings --\n");
	printf("Move: WASD\n");
	printf("Zoom: Mouse wheel\n");
	printf("Rotate: ALT + WASD\n");
	printf("Change movement speed: UP/DOWN\n");
	printf("Change rotation speed: LEFT/RIGHT\n");
	printf("Show source light(s): L\n");
	printf("Change post-process: P (Shift-P to go backwards)\n");
	printf("Anti-aliasing: K\n");
	printf("Show FPS: F\n");
	printf("Save image: SPACE\n");
	printf("Exit program: ESC\n");
	return (CS_OK);
}

enum e_cmd_status	screenshot_cmd(t_state *state)
{
	save_image(state);
	return (CS_OK);
}

enum e_cmd_status	exit_cmd(t_state *state)
{
	(void)state;
	return (CS_EXIT);
}
