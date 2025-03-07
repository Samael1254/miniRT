#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt.h"
#include <stdbool.h>

static void	add_ambient_light(t_state *state, char **split)
{
	t_color	color;
	double	brightness;
	bool	has_error;

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
	t_vector3d	pos;
	t_vector3d	rot;
	double		fov_2;
	bool		has_error;

	pos = get_vector(split[1], &has_error);
	rot = get_vector(split[2], &has_error);
	if (!is_vector3d_in_range(rot, -1, 1) || has_error == true
		|| !is_norm_vector_valid(rot))
	{
		ft_free_strtab(split);
		error("parsing", "error on camera position or rotation", state);
	}
	state->scene.camera.pos = pos;
	state->scene.camera.dir = rot;
	fov_2 = ft_atod(split[3]) / 2;
	if (fov_2 < 0 || fov_2 > 180)
	{
		ft_free_strtab(split);
		error("parsing", "error of the camera fov", state);
	}
	state->scene.camera.fov_2 = ft_deg_to_rad(fov_2);
}

static void	add_light(t_state *state, char **split)
{
	t_vector3d	pos;
	double		brightness;
	t_color		color;
	bool		has_error;

	pos = get_vector(split[1], &has_error);
	brightness = ft_atod(split[2]);
	if (brightness < 0 || brightness > 1 || has_error == true)
	{
		ft_free_strtab(split);
		error("wrong parameter value", "light brightness not in [0-1]", state);
	}
	color = get_color(split[3], &has_error);
	if (has_error == true)
	{
		ft_free_strtab(split);
		error("parsing", "error of ambiant light colors", state);
	}
	state->scene.p_light.pos = pos;
	state->scene.p_light.brightness = brightness;
	state->scene.p_light.color = color;
}

int	insert_in_struct(t_state *state, char **split)
{
	if (!*split)
		return (-1);
	if (!ft_strncmp(split[0], "A", 1))
		add_ambient_light(state, split);
	else if (!ft_strncmp(split[0], "C", 1))
		add_camera(state, split);
	else if (!ft_strncmp(split[0], "L", 1))
		add_light(state, split);
	else if (!ft_strncmp(split[0], "sp", 2))
		add_object_to_list(state, split);
	else if (!ft_strncmp(split[0], "pl", 2))
		add_object_to_list(state, split);
	else if (!ft_strncmp(split[0], "cy", 2))
		add_object_to_list(state, split);
	else if (ft_strcmp(split[0], "\n"))
	{
		split[0][ft_strlen(split[0]) - 1] = '\0';
		warning("no such object type", split[0]);
	}
	return (0);
}
