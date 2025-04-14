/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_errors_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:09 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:09 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_ERRORS_BONUS_H
# define MINIRT_ERRORS_BONUS_H

# include <stdbool.h>
# include "minirt_defs_bonus.h"

// check_arguments_bonus.c
void			check_arguments(int argc, char **argv);

// errors_bonus.c
unsigned int	warnings_number(bool add);
void			warning(char const *type, char const *msg);
void			info(char const *type, char const *msg);
void			error(char const *type, char const *msg, t_state *state);

#endif // !MINIRT_ERRORS_BONUS_H
