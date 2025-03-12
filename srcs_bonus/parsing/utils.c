#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt.h"
#include "ft_strings.h"
#include <stdbool.h>
#include <math.h>

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

t_color	get_color(char *line_color, bool *error)
{
	t_color	color;
	char	**split_color;
	int		r;
	int		g;
	int		b;

	split_color = ft_split(line_color, ',');
	if (!split_color || ft_strtab_size(split_color) < 3)
	{
		if (split_color)
			ft_free_strtab(split_color);
		*error = true;
		return ((t_color){0, 0, 0});
	}
	r = ft_atoi(split_color[0]);
	g = ft_atoi(split_color[1]);
	b = ft_atoi(split_color[2]);
	ft_free_strtab(split_color);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		*error = true;
	else
		*error = false;
	color = (t_color){(unsigned char)r, (unsigned char)g, (unsigned char)b};
	return (color);
}

/*
 *	Check if a vector is in the range min and max (excluded)
 *	Returns (0) if not
 *	Returns (1) if yes
 * */
bool	is_vector3d_in_range(t_vector3d vec, double min, double max)
{
	if (vec.x < min || vec.x > max)
		return (false);
	if (vec.y < min || vec.y > max)
		return (false);
	if (vec.z < min || vec.z > max)
		return (false);
	return (true);
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

bool	is_norm_vector_valid(t_vector3d vec)
{
	if (pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2) != 1)
		return (false);
	return (true);
}
