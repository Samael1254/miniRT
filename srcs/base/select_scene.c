#include "ft_conversion.h"
#include "ft_strings.h"
#include "minirt_base.h"
#include "minirt_errors.h"
#include <dirent.h>
#include <errno.h>
// clang-format off
#include <stdio.h>
#include <readline/readline.h>
// clang-format on
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool is_scene(const char *filename)
{
	char *file_ext;

	file_ext = ft_strrchr(filename, '.');
	if (!file_ext)
		return (false);
	if (file_ext == filename)
		return (false);
	if (ft_strcmp(file_ext, ".rt"))
		return (false);
	return (true);
}

static int count_scenes(void)
{
	DIR                 *d;
	const struct dirent *dir;
	int                  count;

	d = opendir("maps");
	if (!d)
		error("could not select any scene, maps/ directory not found", "please provide a .rt scene file as argument",
		      NULL);
	count = 0;
	while (true)
	{
		dir = readdir(d);
		if (!dir)
			break;
		if (is_scene((dir->d_name)))
			count++;
	}
	closedir(d);
	return (count);
}

static char **load_available_scenes(int count)
{
	int                  i;
	DIR                 *d;
	const struct dirent *dir;
	char               **scenes;

	info(NULL, "Scene selection");
	if (count == 0)
		error("could not find any valid scene in maps/", "please provide a .rt scene file as argument", NULL);
	scenes = malloc((count + 1) * sizeof(char *));
	if (!scenes)
		error("malloc failed", "in select_scene", NULL);
	d = opendir("maps");
	if (!d)
	{
		free(scenes);
		error("failed to open maps directory", strerror(errno), NULL);
	}
	i = 0;
	while (i < count)
	{
		dir = readdir(d);
		if (!dir)
			break;
		if (is_scene((dir->d_name)))
			scenes[i++] = ft_strdup(dir->d_name);
	}
	scenes[i] = NULL;
	closedir(d);
	return (scenes);
}

static void print_available_scenes(char **scenes)
{
	int i;

	printf("Available scenes:\n\n");
	i = 0;
	while (scenes[i])
	{
		printf("\e[33m%2d.\e[34m %s\e[0m\n", i + 1, scenes[i]);
		i++;
	}
}

char *select_scene(void)
{
	int    scene_index;
	int    count;
	char **scenes;
	char  *user_input;
	char  *scene;

	count = count_scenes();
	scenes = load_available_scenes(count);
	print_available_scenes(scenes);
	printf("\nPlease select a scene to launch by entering its \e[33mindex\e[0m\n");
	while (true)
	{
		user_input = readline("> ");
		if (!user_input)
		{
			ft_free_strtab(scenes);
			error(NULL, "input stopped or crashed", NULL);
		}
		scene_index = ft_atoi(user_input);
		if (scene_index > 0 && scene_index <= count && ft_str_is_number(user_input))
		{
			free(user_input);
			break;
		}
		free(user_input);
		printf("Please enter a \e[32mvalid\e[0m scene \e[33mindex\e[0m ");
		printf("(between 1 and %d)\n", count);
	}
	scene = ft_strjoin("maps/", scenes[scene_index - 1]);
	ft_free_strtab(scenes);
	return (scene);
}
