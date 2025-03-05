#include "minirt.h"
#include "libft.h"

/*
 * return a t_vector3d containing the vector RGB based on the line
 * with this format `XXX,XXX,XXX`
 * Error: returns -1,-1,-1 if an error occured
 * */
t_vector3d	get_vector(char *line_vector)
{
	t_vector3d	vector;
	char		**split_vector;
	
	split_vector = ft_split(line_vector, ',');
	if (!split_vector)
		return ((t_vector3d){-1, -1, -1});
	vector.x = ft_atod(split_vector[0]);
	vector.y = ft_atod(split_vector[1]);
	vector.z = ft_atod(split_vector[2]);
	ft_free_strtab(split_vector);
	return (vector);
}

/*
 *	Check if a vector is in the range min and max (excluded)
 *	Returns (0) if not
 *	Returns (1) if yes
 * */
int	is_vector3d_in_range(t_vector3d vec, double min, double max)
{
	if (vec.x < min || vec.x > max)
		return (0);
	if (vec.y < min || vec.y > max)
		return (0);
	if (vec.z < min || vec.z > max)
		return (0);
	return (1);
}

