#include "minirt.h"
#include "minirt_defs.h"

void	put_pixel(t_img_data *img, t_ivector2d coords, t_color color)
{
	int		offset;
	char	*mem_pos;

	if (!(coords.x > 0 && coords.x < WIN_X) || !(coords.y > 0
			&& coords.y < WIN_Y))
	{
		error("put pixel", "pixel coords outside of window");
		return ;
	}
	offset = coords.y * img->line_len + coords.x * (img->bp_pixel) / 8;
	mem_pos = img->addr + offset;
	*(unsigned int *)mem_pos = rgb_to_int(color);
}
