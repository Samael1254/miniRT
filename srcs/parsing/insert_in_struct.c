#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt.h"
#include <stdbool.h>

static void	add_ambient_light(t_state *state, char **split)
{
	t_color	color;
	double	brightness;
	bool	error;

	brightness = ft_atod(split[1]);
	if (brightness < 0 || brightness > 1)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "brightness of ambiant light is wrong", state);
	}
	state->scene.a_light.brightness = brightness;
	color = get_color(split[2], &error);
	if (error == true)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of ambiant light colors", state);
	}
	state->scene.a_light.color = color;
}

static void	add_camera(t_state *state, char **split)
{
	t_vector3d	pos;
	t_vector3d	rot;
	double		fov_2;
	bool		error;

	pos = get_vector(split[1], &error);
	rot = get_vector(split[2], &error);
	if (!is_vector3d_in_range(rot, -1, 1) || error == true)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of ambiant light colors", state);
	}
	state->scene.camera.pos = pos;
	state->scene.camera.dir = rot;
	fov_2 = ft_atod(split[3]) / 2;
	if (fov_2 < 0 || fov_2 > 180)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of the camera fov", state);
	}
	state->scene.camera.fov_2 = ft_deg_to_rad(fov_2);
}
// TODO: mettre une verification sur les norme vector
// somme des carres des composantes doivent etre egales a un
// utiliser pow de math.h
static void	add_light(t_state *state, char **split)
{
	t_vector3d	pos;
	double		brightness;
	t_color		color;
	bool		error;

	pos = get_vector(split[1], &error);
	brightness = ft_atod(split[2]);
	if (brightness < 0 || brightness > 1 || error == true)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of the camera fov", state);
	}
	color = get_color(split[3], &error);
	if (error == true)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of ambiant light colors", state);
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
	if (!ft_strncmp(split[0], "C", 1))
		add_camera(state, split);
	if (!ft_strncmp(split[0], "L", 1))
		add_light(state, split);
	if (!ft_strncmp(split[0], "sp", 2))
		add_object_to_list(state, split);
	if (!ft_strncmp(split[0], "pl", 2))
		add_object_to_list(state, split);
	if (!ft_strncmp(split[0], "cy", 2))
		add_object_to_list(state, split);
	return (0);
}
