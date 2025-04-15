/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt_defs.h"

t_color	scale_color(t_color color, double lambda)
{
	t_color	lit_color;
	int		convert;

	convert = ft_clamp(color.r * lambda, 0, 255);
	lit_color.r = convert;
	convert = ft_clamp(color.g * lambda, 0, 255);
	lit_color.g = convert;
	convert = ft_clamp(color.b * lambda, 0, 255);
	lit_color.b = convert;
	return (lit_color);
}

t_color	absorb_colors(t_color color1, t_color color2)
{
	t_color	avg;

	avg.r = color1.r * (double)color2.r / 255;
	avg.g = color1.g * (double)color2.g / 255;
	avg.b = color1.b * (double)color2.b / 255;
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

t_color	lerp_colors(t_color color1, t_color color2, double lambda)
{
	t_color	lerp;

	color1 = scale_color(color1, lambda);
	color2 = scale_color(color2, 1 - lambda);
	lerp = add_colors(color1, color2);
	return (lerp);
}
