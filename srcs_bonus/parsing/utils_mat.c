#include "ft_strings.h"
#include "minirt_bonus.h"
#include "mlx.h"
#include <fcntl.h>
#include <stddef.h>

void	*get_normal_map_img(t_state *state, char *filename, t_material *mat)
{
	char	*n;
	void	*img;

	n = ft_strchr(filename, '\n');
	if (n)
		*n = '\0';
	img = mlx_xpm_file_to_image(state->display, filename,
			&mat->img_normal_map_width, &mat->img_normal_map_height);
	if (!img)
		error("normal map", "loading error", state);
	mlx_put_image_to_window(state->display, state->win, img, 0, 0);
	return (img);
}
