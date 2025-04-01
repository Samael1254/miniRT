#include "ft_strings.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "mlx.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>

void	get_normal_map_img(t_state *state, char *filename, t_material *mat)
{
	char	*n;
	int		width;
	int		height;

	if (!ft_strcmp(filename, "0"))
	{
		mat->img_normal.img = NULL;
		return ;
	}
	n = ft_strchr(filename, '\n');
	if (n)
		*n = '\0';
	mat->img_normal.img = mlx_xpm_file_to_image(state->display, filename,
			&width, &height);
	if (!mat->img_normal.img)
		error("normal map", "loading error", state);
	mat->img_normal.height = height;
	mat->img_normal.addr = mlx_get_data_addr(mat->img_normal.img,
			&mat->img_normal.bp_pixel, &mat->img_normal.line_len,
			&mat->img_normal.endian);
}

void	get_texture_map_img(t_state *state, char *filename, t_material *mat)
{
	char	*n;
	int		width;
	int		height;

	if (!ft_strcmp(filename, "0"))
	{
		mat->img_texture.img = NULL;
		return ;
	}
	n = ft_strchr(filename, '\n');
	if (n)
		*n = '\0';
	mat->img_texture.img = mlx_xpm_file_to_image(state->display, filename,
			&width, &height);
	if (!mat->img_texture.img)
		error("texture", "loading error", state);
	mat->img_texture.height = height;
	mat->img_texture.addr = mlx_get_data_addr(mat->img_texture.img,
			&mat->img_texture.bp_pixel, &mat->img_texture.line_len,
			&mat->img_texture.endian);
}
