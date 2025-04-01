#include "ft_algebra.h"
#include "minirt_bonus.h"
#include "minirt_defs_bonus.h"
#include <stdio.h>

static int	rgb_to_int(t_color color)
{
	color.a *= 2.55;
	return (color.a << 24 | color.r << 16 | color.g << 8 | color.b << 0);
}

static t_color	int_to_rgb(int colorint)
{
	t_color	color;

	color.r = (colorint >> 16) & 0xFF;
	color.g = (colorint >> 8) & 0xFF;
	color.b = colorint & 0xFF;
	color.a = (colorint >> 24) & 0xFF;
	return (color);
}

void	put_pixel(t_img_data *img, t_ivec2 coords, t_color color)
{
	int		offset;
	char	*mem_pos;

	if (!(coords.x >= 0 && coords.x < WIN_X) || !(coords.y >= 0
			&& coords.y < WIN_Y))
	{
		warning("put pixel", "pixel coords outside of window");
		printf("x: %d, y: %d\n", coords.x, coords.y);
		return ;
	}
	offset = coords.y * img->line_len + coords.x * (img->bp_pixel) / 8;
	mem_pos = img->addr + offset;
	*(unsigned int *)mem_pos = rgb_to_int(color);
}

t_color	get_pixel_color(t_img_data texture, t_vec2 uv)
{
	unsigned int	color;
	int				offset;
	t_ivec2			xy;

	xy.x = uv.x * texture.line_len / (texture.bp_pixel) * 8;
	xy.y = uv.y * texture.height;
	offset = xy.y * texture.line_len + xy.x * (texture.bp_pixel) / 8;
	color = *(unsigned int *)(texture.addr + offset);
	return (int_to_rgb(color));
}
