#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt_bonus.h"
#include <stdbool.h>

/*
 * Return a t_vector3d containing the vector RGB based on the line
 * with this format `XXX,XXX,XXX`
 * Takes in parameter a pointer on bool in order to catch an error
 * on the split malloc
 * Error: returns -1,-1,-1 if an error occured
 * */
t_vector3d	get_vector(char *line_vector, bool *error)
{
	t_vector3d	vector;
	char		**split_vector;

	split_vector = ft_split(line_vector, ',');
	if (!ft_check_split_data(split_vector))
	{
		if (split_vector)
			ft_free_strtab(split_vector);
		*error = true;
		return ((t_vector3d){-1, -1, -1});
	}
	vector.x = ft_atod(split_vector[0]);
	vector.y = ft_atod(split_vector[1]);
	vector.z = ft_atod(split_vector[2]);
	ft_free_strtab(split_vector);
	*error = false;
	return (vector);
}

static unsigned char	get_transparency(char *line, bool *error)
{
	if (!line || !*line)
		return (100);
	if (*line == '1')
	{
		if (line[1] != '\0')
			*error = true;
		return (100);
	}
	else if (*line == '0')
		return (ft_atod(line) * 100);
	else
		*error = true;
	return (100);
}

t_color	get_color(char *line_color, bool *error)
{
	t_color	color;
	char	**split_color;

	split_color = ft_split(line_color, ',');
	if (!split_color || ft_strtab_size(split_color) < 3 || ft_strtab_size(split_color) > 4)
	{
		if (split_color)
			ft_free_strtab(split_color);
		*error = true;
		return ((t_color){0, 0, 0, 0});
	}
	color.r = ft_atoi(split_color[0]);
	color.g = ft_atoi(split_color[1]);
	color.b = ft_atoi(split_color[2]);
	if (ft_strtab_size(split_color) == 4)
		color.a = get_transparency(split_color[3], error);
	else
		color.a = 100;
	ft_free_strtab(split_color);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 ||
		color.b < 0 || color.b > 255 || color.a < 0 || color.a > 100)
		*error = true;
	else
		*error = false;
	return (color);
}

/*
 *	Check if a vector is in the range min and max (excluded)
 *	Returns (0) if not
 *	Returns (1) if yes
 * */
bool	is_t_color_valid(t_color color, double min, double max)
{
	if (color.r < min || color.r > max)
		return (false);
	if (color.g < min || color.g > max)
		return (false);
	if (color.b < min || color.b > max)
		return (false);
	return (true);
}
