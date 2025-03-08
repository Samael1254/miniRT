#include "ft_math.h"
#include "minirt.h"
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

t_color	lerp_colors(t_color color1, t_color color2, double lambda)
{
	t_color	lerp;

	if (!ft_in_rangef(lambda, 0., 1.))
	{
		warning("bad lerp lambda", "should be in range [0-1]");
		lambda = ft_clampf(lambda, 0., 1.);
	}
	lerp.r = (unsigned char)((double)color1.r + (double)(color2.r - color1.r)
			* lambda);
	lerp.g = (unsigned char)((double)color1.g + (double)(color2.g - color1.g)
			* lambda);
	lerp.b = (unsigned char)((double)color1.b + (double)(color2.b - color1.b)
			* lambda);
	return (lerp);
}

t_color	average_colors(t_color color1, t_color color2)
{
	return (lerp_colors(color1, color2, 0.5));
}

t_color	get_sky_color(t_ray ray)
{
	const t_color	color1 = {255, 255, 255};
	const t_color	color2 = {42, 162, 242};
	t_color			sky_color;

	sky_color = lerp_colors(color1, color2, (ray.direction.y + 1) / 2);
	return (sky_color);
}
