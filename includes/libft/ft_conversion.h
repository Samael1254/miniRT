/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:30 by gfulconi          #+#    #+#             */
/*   Updated: 2024/11/22 16:21:15 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERSION_H
# define FT_CONVERSION_H

// Converts a string to an integer
int		ft_atoi(const char *nptr);
// Converts an integer to a string
char	*ft_itoa(int nb);

// Converts a string to a double
double	ft_atod(const char *nptr);

// Converts a string to an integer in the specified base
int		ft_atoi_base(char *str, char *base);
// Converts an integer in the specified base to a string
char	*ft_itoa_base(int nb, char *base);

// Converts a string representing an integer in a specified base to its
// representation in another base
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

// Checks if the string can represent a valid base
int		ft_check_base_errors(char *b);

#endif
