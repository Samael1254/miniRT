/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 15:50:55 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "minirt_errors.h"
#include "stddef.h"

static void	check_filename(char **argv)
{
	char	*file_ext;

	file_ext = ft_strrchr(argv[1], '.');
	if (!file_ext)
		error("wrong filename", "no file extension (.rt file needed)", NULL);
	if (file_ext == argv[1])
		error("wrong filename", "no filename before extension", NULL);
	if (ft_strcmp(file_ext, ".rt"))
		error("wrong filename", "bad file extension (.rt file needed)", NULL);
}

void	check_arguments(int argc, char **argv)
{
	if (argc == 1)
		return ;
	if (argc > 2)
		error("wrong arguments", "too many arguments (only one accepted)",
			NULL);
	check_filename(argv);
}
