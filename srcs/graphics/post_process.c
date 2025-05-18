/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 16:25:34 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include "mlx.h"

t_color	post_process_color(t_color color, t_ivec2 coords,
		enum e_post_process post_process)
{
	t_color	processed_color;

	processed_color = color;
	switch (post_process)
	{
	case PP_VIGNETTE:
		processed_color = vignette(processed_color, coords);
		break ;
	case PP_GAMMA:
		processed_color = gamma_correction(processed_color);
		break ;
	case PP_SEPIA:
		processed_color = sepia_tone(processed_color);
		break ;
	case PP_GRAY:
		processed_color = gray_tone(processed_color);
		break ;
	case PP_SCANLINES:
		processed_color = scanlines(processed_color, coords);
		break ;
	case PP_SATURATION:
		processed_color = saturation_boost(processed_color);
		break ;
	case PP_POSTER:
		processed_color = posterization(processed_color);
		break ;
	case PP_NEGATIVE:
		processed_color = negative(processed_color);
		break ;
	case PP_NONE:
		break ;
	}
	return (processed_color);
}

void	post_process(t_state *state)
{
	t_img_data	processed_img;
	t_ivec2		coords;

	processed_img.img = mlx_new_image(state->display, WIN_X, WIN_Y);
	if (!processed_img.img)
		error("post_process", "failed to create processed image", state);
	processed_img.addr = mlx_get_data_addr(processed_img.img,
			&processed_img.bp_pixel, &processed_img.line_len,
			&processed_img.endian);
	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			put_pixel(&processed_img, coords,
				post_process_color(get_pixel_color(state->img_data, coords),
					coords, state->post_process));
			coords.x++;
		}
		coords.y++;
	}
	if (state->processed_img.img)
		mlx_destroy_image(state->display, state->processed_img.img);
	state->processed_img = processed_img;
}
