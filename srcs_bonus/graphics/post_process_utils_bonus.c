#include "minirt_graphics_bonus.h"
#include "ft_math.h"
#include <math.h>

t_color	negative(t_color color)
{
	t_color	neg;

	neg.r = 255 - color.r;
	neg.g = 255 - color.g;
	neg.b = 255 - color.b;
	return (neg);
}

t_color	gamma_correction(t_color color)
{
	const double	gamma_inv = 1 / 1.3;
	t_color			corrected_color;

	corrected_color.r = (unsigned char)(pow((double)color.r / 255, gamma_inv)
			* 255);
	corrected_color.g = (unsigned char)(pow((double)color.g / 255, gamma_inv)
			* 255);
	corrected_color.b = (unsigned char)(pow((double)color.b / 255, gamma_inv)
			* 255);
	return (corrected_color);
}

t_vec3	ldr_to_hdr_color(t_color ldr)
{
	t_vec3	hdr;

	hdr.x = (double)ldr.r / 255;
	hdr.y = (double)ldr.g / 255;
	hdr.z = (double)ldr.b / 255;
	return (hdr);
}

t_color	hdr_to_ldr_color(t_vec3 hdr)
{
	t_color	ldr;

	ldr.r = (unsigned char)ft_clampf(hdr.x * 255, 0, 255);
	ldr.g = (unsigned char)ft_clampf(hdr.y * 255, 0, 255);
	ldr.b = (unsigned char)ft_clampf(hdr.z * 255, 0, 255);
	return (ldr);
}
