/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorts.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:58 by gfulconi          #+#    #+#             */
/*   Updated: 2024/11/22 01:03:45 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORTS_H
# define FT_SORTS_H

void	selection_sort_int(int *tab, int size);
void	bubble_sort_int(int *tab, int size);
int		*merge_sort(int *tab, int size);

void	ft_swap_int(int *a, int *b);

#endif
