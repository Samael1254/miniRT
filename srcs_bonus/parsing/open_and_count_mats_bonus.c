#include "ft_conversion.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "get_next_line.h"
#include "minirt_defs_bonus.h"
#include "minirt_errors_bonus.h"
#include "minirt_parsing_bonus.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	insert_data_in_mat(t_state *state, char **line_mat, int i)
{
	int			tab_len;
	t_material	mat;
	bool		has_error;

	tab_len = ft_strtab_size(line_mat);
	if (tab_len != 7 && tab_len != 9)
		return (ft_free_strtab(line_mat), error(".mrt",
				"Enter 7 or 9 parameters in line", state));
	mat.kd = get_color(line_mat[M_KD], &has_error);
	mat.ks = get_color(line_mat[M_KS], &has_error);
	mat.ka = get_color(line_mat[M_KA], &has_error);
	mat.specularity = ft_atod(line_mat[M_SPEC]);
	mat.reflectance = ft_atod(line_mat[M_REFL]);
	mat.img_texture.img = NULL;
	mat.img_normal.img = NULL;
	if (tab_len == 9)
	{
		if (!get_texture_map_img(state, line_mat[M_TX], &mat))
			return (ft_free_strtab(line_mat), error("unable to load", "texture",
					state));
		if (!get_normal_map_img(state, line_mat[M_NM], &mat))
			return (ft_free_strtab(line_mat), error("unable to load",
					"normal map", state));
	}
	state->mats_tab[i] = mat;
}

static void	material_handling(t_state *state, int fd)
{
	int		i;
	char	*line;
	char	**tmp_split;

	i = 1;
	tmp_split = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp_split = ft_split_charset(line, " \t\n");
		free(line);
		if (!tmp_split)
			error("malloc", "material_handling", state);
		if (tmp_split[0] && !ft_strncmp(tmp_split[0], "mt", 2))
			insert_data_in_mat(state, tmp_split, i++);
		ft_free_strtab(tmp_split);
	}
}

static void	count_nb_mats(t_state *state, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp("mt", line, 2))
			state->len_mats_tab++;
		free(line);
	}
	if (state->len_mats_tab == 0)
		error("len_mats_tab", "is null...", state);
}

static int	line_mt_handler(t_state *state, char *line_mat)
{
	char	**tmp_split;
	int		fd;

	tmp_split = ft_split_charset(line_mat, " \t\n");
	free(line_mat);
	if (!tmp_split)
		return (1);
	if (ft_strtab_size(tmp_split) > 2)
		return (ft_free_strtab(tmp_split), 1);
	fd = open(tmp_split[1], O_RDONLY);
	if (fd <= 0)
	{
		ft_free_strtab(tmp_split);
		error("open", "can't open material file", state);
	}
	count_nb_mats(state, fd);
	close(fd);
	fd = open(tmp_split[1], O_RDONLY);
	ft_free_strtab(tmp_split);
	if (fd <= 0)
		error("open", "can't open material file", state);
	state->mats_tab = ft_calloc(state->len_mats_tab + 1, sizeof(t_material));
	if (!state->mats_tab)
		error("malloc", "open_and_count_mats", state);
	return (material_handling(state, fd), 0);
}

/*
 * Counts number of materials in order to alloc the tab.
 * Returns an fd like an normal open. Just counts before.
 * Mallocs the mats_tab in t_state.
 * */
int	open_and_count_mats(t_state *state, char *filename)
{
	int		fd;
	int		nb_mt_found;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		error("wrong filename", "cannot open file", state);
	nb_mt_found = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp("MT", line, 2))
		{
			if (line_mt_handler(state, line))
				error(NULL, "problem on material line", state);
			nb_mt_found++;
		}
		else
			free(line);
	}
	if (close(fd) == -1 && nb_mt_found != 1)
		error("materials", "need one and only one MT line", state);
	return (open(filename, O_RDONLY));
}
