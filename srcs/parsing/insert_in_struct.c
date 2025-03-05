#include "minirt.h"
#include "libft.h"

static void	add_ambient_light(t_state *state, char **split)
{
	t_vector3d	color;
	double		intensity;

	intensity = ft_atod(split[1]);
	if (intensity < 0 || intensity > 1)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "intensity of ambiant light is wrong", state);
	}
	state->scene.a_light.intensity = intensity;
	color = get_vector(split[2]);
	if (color.x == -1 || !is_vector3d_in_range(color, 0, 255))
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
	int			fov;

	pos = get_vector(split[1]);
	rot = get_vector(split[2]);
	if (!is_vector3d_in_range(rot, -1, 1))
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of ambiant light colors", state);
	}
	state->scene.camera.pos = pos;
	state->scene.camera.rot = rot;
	fov = ft_atoi(split[3]);
	if (fov < 0 || fov > 180)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of the camera fov", state);
	}
	state->scene.camera.fov = fov;
}

static void	add_light(t_state *state, char **split)
{
	t_vector3d	pos;
	double		brightness;
	t_vector3d	color;

	pos = get_vector(split[1]);
	brightness = ft_atod(split[2]);
	if (brightness < 0 || brightness > 1)
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of the camera fov", state);
	}
	color = get_vector(split[3]);
	if (!is_vector3d_in_range(color, 0, 255))
	{
		ft_free_strtab(split);
		fatal_error("parsing", "error of ambiant light colors", state);
	}
	state->scene.p_light.pos = pos;
	state->scene.p_light.brightness = brightness;
	state->scene.p_light.color = color;
}

int	retrieve_data(t_state *state, char **split)
{
	if (!*split)
		return (-1);
	if (!ft_strncmp(split[0], "A", 1))
		add_ambient_light(state, split);
	if (!ft_strncmp(split[0], "C", 1))
		add_camera(state, split);
	if (!ft_strncmp(split[0], "L", 1))
		add_light(state, split);
	else
		add_object_to_list(state, split);
	return (0);
}
