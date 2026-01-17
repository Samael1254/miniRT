/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:37 by gfulconi          #+#    #+#             */
/*   Updated: 2024/11/22 16:00:41 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHARS_H
# define FT_CHARS_H

// Checks if the character is a space character
int	ft_isspace(int c);
// Checks if the character is a digit
int	ft_isdigit(int c);
// Checks if the character is defined in the ASCII table
int	ft_isascii(int c);
// Checks if the character is a letter of the alphabet
int	ft_isalpha(int c);
// Checks if the character is a letter or a digit
int	ft_isalnum(int c);
// Checks if the character is printable
int	ft_isprint(int c);
// Checks if the character is in the given charset
int	ft_isincharset(const char c, const char *charset);
// Converts a lowercase letter to uppercase
int	ft_toupper(int c);
// Converts a uppercase letter to lowercase
int	ft_tolower(int c);
// Returns the first index of the character inside the giving string
int	ft_get_char_index(const char c, const char *str);

#endif
