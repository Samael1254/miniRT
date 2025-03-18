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

t_color	lerp_colors(t_color color1, t_color color2, double lambda)
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

t_color	absorb_colors(t_color color1, t_color color2)
{
	t_color	avg;

	avg.r = color1.r * ((double)color2.r / 255);
	avg.g = color1.g * ((double)color2.g / 255);
	avg.b = color1.b * ((double)color2.b / 255);
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

t_color	blend_colors(t_color color1, t_color color2)
{
	t_color	avg;

	avg.r = (color1.r + color2.r) / 2;
	avg.g = (color1.g + color2.g) / 2;
	avg.b = (color1.b + color2.b) / 2;
	return (avg);
}

t_color	init_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_material	get_sky_material(t_ray ray)
{
	t_material		sky_material;
	const t_color	color1 = {255, 174, 69};
	const t_color	color2 = {42, 162, 242};

	sky_material.kd = lerp_colors(color1, color2, (ray.direction.y + 1) / 2);
	sky_material.ks = init_color(0, 0, 0);
	sky_material.ka = init_color(0, 0, 0);
	sky_material.specularity = 0;
	return (sky_material);
}
