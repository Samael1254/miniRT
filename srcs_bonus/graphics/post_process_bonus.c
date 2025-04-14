#include "ft_algebra.h"
#include "minirt_defs_bonus.h"
#include "minirt_graphics_bonus.h"
#include <math.h>

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
