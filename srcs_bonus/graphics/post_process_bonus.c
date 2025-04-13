#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include <math.h>

static t_color	vignette(t_color color, t_ivec2 coords)
{
	double			vignette_scale;
	const double	intensity = 0.5;
	const double	dx = (double)(coords.x - WIN_X / 2) / (double)(WIN_X / 2);
	const double	dy = (double)(coords.y - WIN_Y / 2) / (double)(WIN_Y / 2);

	vignette_scale = 1 - (dx * dx + dy * dy) * intensity;
	return (scale_color(color, vignette_scale));
}

static t_color	negative(t_color color)
{
	t_color	neg;

	neg.r = 255 - color.r;
	neg.g = 255 - color.g;
	neg.b = 255 - color.b;
	return (neg);
}

static t_color	gamma_correction(t_color color)
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

static t_color	sepia_tone(t_color color)
{
	t_vec3	hdr;
	t_vec3	sepia;

	hdr = ldr_to_hdr_color(color);
	sepia.x = hdr.x * .393 + hdr.y * .769 + hdr.z * .189;
	sepia.y = hdr.x * .349 + hdr.y * .686 + hdr.z * .168;
	sepia.z = hdr.x * .272 + hdr.y * .534 + hdr.z * .131;
	return (hdr_to_ldr_color(sepia));
}

static t_color	gray_tone(t_color color)
{
	double	gray;

	gray = ft_dot_vec3(ldr_to_hdr_color(color), ft_set_vec3(0.299, 0.587,
				0.114));
	return (hdr_to_ldr_color(ft_init_vec3(gray)));
}

static t_color	scanlines(t_color color, t_ivec2 coords)
{
	if ((coords.y / 4) % 2)
		return (color);
	return (scale_color(color, 0.7));
}

static t_color	saturation_boost(t_color color)
{
	double			intensity;
	const double	saturation = 1.5;

	intensity = ft_dot_vec3(ldr_to_hdr_color(color), ft_set_vec3(0.2126, 0.7152,
				0.0722));
	return (lerp_colors(color, hdr_to_ldr_color(ft_init_vec3(intensity)),
			saturation));
}

static t_color	posterization(t_color color)
{
	const int	levels = 7;
	t_vec3		hdr;

	hdr = ft_scale_vec3(levels, ldr_to_hdr_color(color));
	hdr.x = floor(hdr.x) / (double)levels;
	hdr.y = floor(hdr.y) / (double)levels;
	hdr.z = floor(hdr.z) / (double)levels;
	return (hdr_to_ldr_color(hdr));
}

t_color	post_process(t_color color, t_ivec2 coords, const t_state *state)
{
	t_color	processed_color;

	processed_color = color;
	if (state->post_process == PP_VIGNETTE)
		processed_color = vignette(processed_color, coords);
	else if (state->post_process == PP_GAMMA)
		processed_color = gamma_correction(processed_color);
	else if (state->post_process == PP_SEPIA)
		processed_color = sepia_tone(processed_color);
	else if (state->post_process == PP_GRAY)
		processed_color = gray_tone(processed_color);
	else if (state->post_process == PP_SCANLINES)
		processed_color = scanlines(processed_color, coords);
	else if (state->post_process == PP_SATURATION)
		processed_color = saturation_boost(processed_color);
	else if (state->post_process == PP_POSTER)
		processed_color = posterization(processed_color);
	else if (state->post_process == PP_NEGATIVE)
		processed_color = negative(processed_color);
	return (processed_color);
}
