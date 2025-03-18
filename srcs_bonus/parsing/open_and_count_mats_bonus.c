#include "minirt_bonus.h"
#include "get_next_line.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include "ft_conversion.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	insert_color_in_mat(t_state *state, char **line_mat, int *i)
{
	t_material	mat;
	bool		error;

	if (ft_strtab_size(line_mat) != 5)
		return ;
	mat.kd = get_color(line_mat[1], &error);
	mat.ks = get_color(line_mat[2], &error);
	mat.ka = get_color(line_mat[3], &error);
	mat.specularity = ft_atod(line_mat[4]);
	state->mats_tab[*i] = mat;
	(*i)++;
}

static void	material_handling(t_state *state, int fd)
{
	int		i;
	char	*line;
	char	**tmp_split;

	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp_split = ft_split_charset(line, " \t");
		free(line);
		if (!tmp_split)
			error("malloc", "material_handling", state);
		if (!ft_strncmp("mt", tmp_split[0], ft_strlen(tmp_split[0])))
			insert_color_in_mat(state, tmp_split, &i);
		ft_free_strtab(tmp_split);
	}
}

#include <stdio.h>
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
	ft_free_strtab(tmp_split);
	if (fd <= 0)
		error("open", "can't open file", state);
	count_nb_mats(state, fd);
	state->mats_tab = ft_calloc(state->len_mats_tab + 1, sizeof(t_material));
	if (!state->mats_tab)
		error("malloc", "open_and_count_mats", state);
	material_handling(state, fd);
	return (0);
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
	close(fd);
	if (nb_mt_found != 1)
		error("materials", "need one and only one MT line", state);
	return (open(filename, O_RDONLY));
}
