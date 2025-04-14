/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_struct_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_parsing_bonus.h"
#include <stdbool.h>

static void	add_ambient_light(t_state *state, char **split)
{
	t_color	color;
	double	brightness;
	bool	has_error;

	ambiant_light_checker(state, split);
	brightness = ft_atod(split[1]);
	if (brightness < 0 || brightness > 1)
	{
		ft_free_strtab(split);
		error("parsing", "brightness of ambiant light is wrong", state);
	}
	state->scene.a_light.brightness = brightness;
	color = get_color(split[2], &has_error);
	if (has_error == true)
	{
		ft_free_strtab(split);
		error("parsing", "error of ambiant light colors", state);
	}
	state->scene.a_light.color = color;
}

static void	add_camera(t_state *state, char **split)
{
	t_vec3	dir;
	double	fov_2;
	bool	has_error;

	dir = get_vector(split[2], &has_error);
	state->scene.camera.pos = get_vector(split[1], &has_error);
	state->scene.camera.dir = dir;
	if (!is_vec3_in_range(dir, -1, 1) || has_error == true)
	{
		ft_free_strtab(split);
		error("parsing", "error on camera position or rotation", state);
	}
	state->scene.camera.x_axis = ft_cross_vec3(dir, ft_set_vec3(0, 1, 0));
	state->scene.camera.y_axis = ft_cross_vec3(state->scene.camera.x_axis, dir);
	fov_2 = ft_atod(split[3]) / 2;
	if (fov_2 < 0 || fov_2 > 90)
	{
		ft_free_strtab(split);
		error("parsing", "error of the camera fov", state);
	}
	state->scene.camera.fov_2 = ft_deg_to_rad(fov_2);
	state->scene.camera.move_step = 5;
	state->scene.camera.rot_step = 15;
}

static void	add_sky(t_state *state, char **split)
{
	bool	has_error;

	state->scene.sky.bottom = get_color(split[2], &has_error);
	state->scene.sky.top = get_color(split[1], &has_error);
	if (has_error == true)
	{
		ft_free_strtab(split);
		error("wrong parameter value", "sky must be valid colors.", state);
	}
}

int	insert_in_struct(t_state *state, char **split)
{
	if (!ft_strncmp(split[0], "A", ft_strlen(split[0])))
		return (add_ambient_light(state, split), 2);
	else if (!ft_strncmp(split[0], "C", ft_strlen(split[0])))
		return (add_camera(state, split), 2);
	else if (!ft_strncmp(split[0], "L", ft_strlen(split[0])))
		return (add_lights_to_list(state, split), 2);
	else if (!ft_strncmp(split[0], "SKY", ft_strlen(split[0])))
		return (add_sky(state, split), 2);
	else if (!ft_strncmp(split[0], "sp", ft_strlen(split[0])))
		add_object_to_list(state, split);
	else if (!ft_strncmp(split[0], "pl", ft_strlen(split[0])))
		add_object_to_list(state, split);
	else if (!ft_strncmp(split[0], "cy", ft_strlen(split[0])))
		add_object_to_list(state, split);
	else if (!ft_strncmp(split[0], "co", ft_strlen(split[0])))
		add_object_to_list(state, split);
	else if (!ft_strncmp(split[0], "mesh", ft_strlen(split[0])))
		add_object_to_list(state, split);
	else if (ft_strcmp(split[0], "\n") && ft_strncmp(split[0], "MT", 2))
	{
		split[0][ft_strlen(split[0])] = '\0';
		return (warning("no such object type", split[0]), 1);
	}
	return (0);
}
