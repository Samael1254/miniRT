#ifndef MINIRT_GRAPHICS_BONUS_H
# define MINIRT_GRAPHICS_BONUS_H

# include "minirt_defs_bonus.h"

// color_bonus.c
t_color	scale_color(t_color color, double lambda);
t_color	add_colors(t_color color1, t_color color2);
t_color	lerp_colors(t_color color1, t_color color2, double lambda);
t_color	absorb_colors(t_color color1, t_color color2);

// color_utils_bonus.c
t_color	init_color(unsigned char r, unsigned char g, unsigned char b);
t_color	get_sky_color(t_sky sky, t_ray ray);

// graphics_bonus.c
void	put_pixel(t_img_data *img, t_ivec2 coords, t_color color);
t_color	get_pixel_color(t_img_data texture, t_vec2 uv);

#endif // !MINIRT_GRAPHICS_BONUS_H
