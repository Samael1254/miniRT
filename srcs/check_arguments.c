#include "minirt.h"
#include "stddef.h"
#include "ft_strings.h"

static int	check_filename(char **argv)
{
	char	*file_ext;

	file_ext = ft_strrchr(argv[1], '.');
	if (!file_ext || file_ext == argv[1])
		return (TRUE);
	if (!ft_strcmp(file_ext, ".rt"))
		return (FALSE);
	return (TRUE);
}

int	check_arguments(int argc, char **argv)
{
	if (argc == 1)
	{
		error(NULL, "no .rt scene file provided");
		return (TRUE);
	}
	if (argc > 2)
	{
		error(NULL, "too many arguments (only one accepted)");
		return (TRUE);
	}
	if (check_filename(argv))
	{
		error(NULL, "error in filename");
		return (TRUE);
	}
	return (FALSE);
}
