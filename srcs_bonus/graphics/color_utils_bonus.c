#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"

static t_color	lerp_colors(t_color color1, t_color color2, double lambda)
{
	t_color	lerp;

	if (!ft_in_rangef(lambda, 0., 1.))
	{
		warning("bad lerp lambda", "should be in range [0-1]");
		lambda = ft_clampf(lambda, 0., 1.);
	}
	lerp.r = (unsigned char)(color1.r + (color2.r - color1.r) * lambda);
	lerp.g = (unsigned char)(color1.g + (color2.g - color1.g) * lambda);
	lerp.b = (unsigned char)(color1.b + (color2.b - color1.b) * lambda);
	return (lerp);
}

t_color	init_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 100;
	return (color);
}

t_color	get_sky_color(t_sky sky, t_ray ray)
{
	t_color	sky_color;

	sky_color = lerp_colors(sky.bottom, sky.top, (ray.direction.y + 1) / 2);
	return (sky_color);
}
