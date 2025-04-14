/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:30 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:30 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_defs.h"
#include "mlx.h"
#include <stdio.h>

static int	rgb_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b << 0);
}

static void	put_pixel(t_img_data *img, t_ivec2 coords, t_color color)
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

void	render_scene(t_state *state, t_ray **rays)
{
	t_ivec2	coords;

	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			put_pixel(&state->img_data, coords, rays[coords.y][coords.x].color);
			coords.x++;
		}
		coords.y++;
	}
	mlx_put_image_to_window(state->display, state->win, state->img_data.img, 0,
		0);
}
