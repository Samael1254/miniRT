#include "minirt_defs.h"

int	rgb_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b << 0);
}

void	apply_brightness(t_color *color, double brightness)
{
	color->r = (unsigned char)((double)color->r * brightness);
	color->g = (unsigned char)((double)color->g * brightness);
	color->b = (unsigned char)((double)color->b * brightness);
}

t_color	average_colors(t_color color1, t_color color2)
{
	t_color	avg;

	avg.r = (unsigned char)(((double)color1.r + (double)color2.r) * 0.5);
	avg.g = (unsigned char)(((double)color1.g + (double)color2.g) * 0.5);
	avg.b = (unsigned char)(((double)color1.b + (double)color2.b) * 0.5);
	return (avg);
}
