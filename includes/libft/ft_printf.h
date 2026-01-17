/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:02:32 by gfulconi          #+#    #+#             */
/*   Updated: 2024/11/22 14:22:27 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// Prints a formatted string to stdin
int	ft_printf(const char *format, ...);

// Prints a formatted string to a file descriptor
int	ft_dprintf(int fd, const char *format, ...);

#endif
