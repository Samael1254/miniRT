#include "ft_strings.h"
#include "minirt_bonus.h"
#include "mlx.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>

void	get_normal_map_img(t_state *state, char *filename, t_material *mat)
{
	char	*n;
	int		width;
	int		height;

	n = ft_strchr(filename, '\n');
	if (n)
		*n = '\0';
	mat->img_texture.img = mlx_xpm_file_to_image(state->display, filename,
			&width, &height);
	printf("%s\n", filename);
	if (!mat->img_texture.img)
		error("normal map", "loading error", state);
	mat->img_texture.addr = mlx_get_data_addr(mat->img_texture.img,
			&mat->img_texture.bp_pixel, &mat->img_texture.line_len,
			&mat->img_texture.endian);
}
