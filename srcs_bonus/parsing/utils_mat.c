#include "ft_conversion.h"
#include "ft_math.h"
#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_parsing_bonus.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

void	init_mat(t_material *mat, char **line_mat, bool *has_error)
{
	mat->kd = get_color(line_mat[M_KD], has_error);
	mat->ks = get_color(line_mat[M_KS], has_error);
	mat->ka = get_color(line_mat[M_KA], has_error);
	mat->specularity = ft_clampf(ft_atod(line_mat[M_SPEC]), 0, 1);
	mat->reflectance = ft_clampf(ft_atod(line_mat[M_REFL]), 0, 1);
	mat->transparency = ft_clampf(ft_atod(line_mat[M_TRANS]), 0, 1);
	mat->refraction = ft_clampf(ft_atod(line_mat[M_REFR]), 1, INFINITY);
	mat->img_texture.img = NULL;
	mat->img_normal.img = NULL;
}

bool	get_normal_map_img(t_state *state, char *filename, t_material *mat)
{
	char	*n;
	int		width;
	int		height;

	if (!ft_strcmp(filename, "0"))
	{
		mat->img_normal.img = NULL;
		return (true);
	}
	n = ft_strchr(filename, '\n');
	if (n)
		*n = '\0';
	mat->img_normal.img = mlx_xpm_file_to_image(state->display, filename,
			&width, &height);
	if (!mat->img_normal.img)
		return (false);
	mat->img_normal.height = height;
	mat->img_normal.addr = mlx_get_data_addr(mat->img_normal.img,
			&mat->img_normal.bp_pixel, &mat->img_normal.line_len,
			&mat->img_normal.endian);
	return (true);
}

bool	get_texture_map_img(t_state *state, char *filename, t_material *mat)
{
	char	*n;
	int		width;
	int		height;

	if (!ft_strcmp(filename, "0"))
	{
		mat->img_texture.img = NULL;
		return (true);
	}
	n = ft_strchr(filename, '\n');
	if (n)
		*n = '\0';
	mat->img_texture.img = mlx_xpm_file_to_image(state->display, filename,
			&width, &height);
	if (!mat->img_texture.img)
		return (false);
	mat->img_texture.height = height;
	mat->img_texture.addr = mlx_get_data_addr(mat->img_texture.img,
			&mat->img_texture.bp_pixel, &mat->img_texture.line_len,
			&mat->img_texture.endian);
	return (true);
}
