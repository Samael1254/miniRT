#include "ft_math.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"

t_color	scale_color(t_color color, double lambda)
{
	t_color	lit_color;

	lit_color.r = (unsigned char)(color.r * lambda);
	lit_color.g = (unsigned char)(color.g * lambda);
	lit_color.b = (unsigned char)(color.b * lambda);
	return (lit_color);
}

t_color	absorb_colors(t_color color1, t_color color2)
{
	t_color	avg;

	avg.r = color1.r * (double)color2.r / 255;
	avg.g = color1.g * (double)color2.g / 255;
	avg.b = color1.b * (double)color2.b / 255;
	return (avg);
}

t_color	add_colors(t_color color1, t_color color2)
{
	t_color	sum;

	sum.r = ft_min(color1.r + color2.r, 255);
	sum.g = ft_min(color1.g + color2.g, 255);
	sum.b = ft_min(color1.b + color2.b, 255);
	return (sum);
}
