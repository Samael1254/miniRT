/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:59:57 by gfulconi          #+#    #+#             */
/*   Updated: 2025/03/05 13:29:48 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include <stddef.h>

// Returns the length of a string
size_t	ft_strlen(const char *str);

// Concatenates two strings by appending one at the end of the other
char	*ft_strcat(char *dest, const char *src);
// Concatenates two strings by appending the first nb characters of one at the
// end of the other
char	*ft_strncat(char *dest, const char *src, size_t nb);

// Copies a string inside another one
char	*ft_strcpy(char *dest, const char *src);
// Copies n characters of a string inside another one
char	*ft_strncpy(char *dest, const char *src, size_t n);

// Returns the difference between the first two different characters of two
// strings (returns 0 if the strings are equal)
int		ft_strcmp(const char *s1, const char *s2);
// Returns the difference between the first two different characters amongst
// the n first characters of two strings (returns 0 if the strings are equal)
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// Creates a new string from appending a character to a string
char	*ft_str_addchar(char *str, char c);
// Creates a new string from appending a string to another
char	*ft_strjoin(char const *s1, char const *s2);
// Creates a new string from appending all strings from a tab next to eachother
char	*ft_strjoin_tab(char **strs, char *sep);

// Returns a pointer to the first occurence of a character in a string
// (NULL if not found)
char	*ft_strchr(const char *s, int c);
// Returns a pointer to the last occurence of a character in a string
// (NULL if not found)
char	*ft_strrchr(const char *s, int c);

// Returns the number of characters in a row that are in the "accept"
// charset sratring from s
size_t	ft_strspn(const char *s, const char *accept);
// Returns the number of characters in a row that are not in the "reject"
// charset sratring from s
size_t	ft_strcspn(const char *s, const char *reject);

// Creates a new string containing the copy of another
char	*ft_strdup(const char *s);
// Creates a new string containing the fisrt n bytes of another at most
char	*ft_strndup(const char *s, size_t n);
// Creates a new string containing a portion of another string
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Creates a string containing the next token defined by the given delimiters
char	*ft_strtok(char *str, const char *delim);

// Returns a pointer to the first occurence of a string inside another one
// (NULL if not found)
char	*ft_strstr(char *str, char *to_find);
// Returns a pointer to the first occurence of a the first n character of a
// string inside another one (NULL if not found)
char	*ft_strnstr(const char *big, const char *little, size_t len);

// Creates a new string by deleting the characters contained in set around
// a given string
char	*ft_strtrim(char const *s1, char const *set);
// Creates a new string by surrounding the given string by the surround
// string in a symetric way
char	*ft_strsurround(char *str, char *surround);

// Creates a tab of strings from splitting a string at every separator
char	**ft_split(char const *s, char c);
// Creates a tab of strings from splitting a string at every separator
// present in charset
char	**ft_split_charset(char const *s, char *charset);
// Counts the number of words in a string separated by a given character
int		ft_count_words(char *s, char sep);
// Frees a table of strings
void	ft_free_strtab(char **tab);
// Returns the size of an array of strings
int		ft_strtab_size(char **tab);

// Calls a function for every character of a string
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
// Creates a new string by applying a function to every character of a string
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// Checks if a string describes a number
int		ft_str_is_number(const char *str);

int		get_char_index(const char c, const char *str);

#endif
