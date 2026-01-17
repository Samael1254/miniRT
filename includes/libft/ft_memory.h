/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:50:16 by gfulconi          #+#    #+#             */
/*   Updated: 2024/11/22 16:33:09 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

# include <stddef.h>

// Returns a pointer to the first occurence of a byte inside a buffer
void	*ft_memchr(const void *s, int c, size_t n);
// Returns the difference between the first different bytes in two buffers,
// returns 0 if they are equal
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Copies the content of a buffer inside another, if both do not overlap
void	*ft_memcpy(void *dest, const void *src, size_t n);
// Copies the content of a buffer inside another, even if they overlap
void	*ft_memmove(void *dest, const void *src, size_t n);
// Fills a buffer with the specified character
void	*ft_memset(void *s, int c, size_t n);
// Fills a buffer with zeros
void	*ft_bzero(void *s, size_t n);
// Allocates a buffer and fills it with zeros
void	*ft_calloc(size_t nmemb, size_t size);

#endif
