#include "ft_algebra.h"
#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt_bonus.h"
#include <stdbool.h>

/*
 * Return a t_vec3 containing the vector RGB based on the line
 * with this format `XXX,XXX,XXX`
 * Takes in parameter a pointer on bool in order to catch an error
 * on the split malloc
 * Error: returns -1,-1,-1 if an error occured
 * */
t_vec3	get_vector(char *line_vector, bool *error)
{
	t_vec3	vector;
	char	**split_vector;

	split_vector = ft_split(line_vector, ',');
	if (!ft_check_split_data(split_vector))
	{
		if (split_vector)
			ft_free_strtab(split_vector);
		*error = true;
		return ((t_vec3){-1, -1, -1});
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
	char	**split;

	split = ft_split(line_color, ',');
	if (!split || ft_strtab_size(split) < 3 || ft_strtab_size(split) > 4)
	{
		if (split)
			ft_free_strtab(split);
		*error = true;
		return ((t_color){0, 0, 0, 0});
	}
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	if (ft_strtab_size(split) == 4)
		color.a = get_transparency(split[3], error);
	else
		color.a = 100;
	ft_free_strtab(split);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255 || color.a < 0 || color.a > 100)
		*error = true;
	else
		*error = false;
	return (color);
}
