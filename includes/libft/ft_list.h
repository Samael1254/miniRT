/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:08 by gfulconi          #+#    #+#             */
/*   Updated: 2025/02/18 13:46:03 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

// Creation

// Creates a single list element
t_list				*ft_create_elem(void *data);
// Creates a full deep copy of a list
t_list				*ft_list_deep_cpy(t_list *src, void *(*dup_fct)(void *),
						void (*free_fct)(void *));
// Creates a shallow copy of a list that points to the same data as the
// original
t_list				*ft_list_shallow_copy(t_list *begin_list);
// Creates a list by applying a given function to every element of a given list
t_list				*ft_list_map(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// Insertion

// Inserts an element containing given data to the back of the list
int					ft_list_push_back(t_list **begin_list, void *data);
// Inserts an element containing given data to the front of the list
int					ft_list_push_front(t_list **begin_list, void *data);
// Inserts an element containing given data at a given index of the list
void				ft_list_insert(t_list **begin_list, void *data,
						unsigned int index);
// Inserts an element containing given data in the list so that it stays sorted
void				ft_sorted_list_insert(t_list **begin_list, void *data,
						int (*cmp)(void *, void *));

// Deletion

// Frees the memory of a single list element and possibly its content
void				ft_delete_elem(t_list *elem, void (*free_fct)(void *));
// Frees the memory of every element inside a list and possibly their content
void				ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
// Deletes elements from the list if their data satisfies the given comparison
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)(void *, void *), void (*free_fct)(void *));
// Deletes the element located at the given index of the list
void				ft_list_delete_at(t_list **begin_list, unsigned int index,
						void (*free_fct)(void *));
// Frees the memory of the end of a list and possibly its content,
// starting at a given index
void				ft_list_clear_from(t_list *begin_list, unsigned int index,
						void (*free_fct)(void *));

// List info

// Returns the number of elements inside the list
unsigned int		ft_list_size(t_list *begin_list);
// Checks if the list is sorted
int					ft_list_is_sorted(t_list *begin_list, int (*cmp)(void *,
							void *));
// Returns the list element containing the smallest int
t_list				*ft_int_list_min(t_list *begin_list);
// Returns the list element containing the largest int
t_list				*ft_int_list_max(t_list *begin_list);

// Navigation

// Returns the last element of the list
t_list				*ft_list_last(t_list *begin_list);
// Returns the element located at the given index of the list
t_list				*ft_list_at(t_list *begin_list, unsigned int nbr);
// Returns the element located at the given index of the list starting from end
t_list				*ft_list_at_end(t_list *begin_list, unsigned int i);
// Returns the first element where the data satisfies the given comparison
t_list				*ft_list_find(t_list *begin_list, void *data_ref,
						int (*cmp)(void *, void *));
// Returns the index of a given element in a list
int					ft_list_index(t_list *begin_list, t_list *elem);
// Returns the index of the first element where the data satisfies the given
// comparison
int					ft_list_find_index(t_list *begin_list, void *data,
						int (*cmp)(void *, void *));

// Sorting, merging and manipulating

// Swaps two elements in the list
void				ft_swap_elem(t_list **begin_list, unsigned int i,
						unsigned int j);
// Reverses the list
void				ft_list_reverse(t_list **begin_list);
// Sorts the list
void				ft_list_sort(t_list **begin_list, int (*cmp)(void *,
							void *));
// Merges two lists by appending one to another
void				ft_list_merge(t_list **begin_list1, t_list *begin_list2);
// Merges two sorted lists and keeps the resulting list sorted
void				ft_sorted_list_merge(t_list **begin_list1,
						t_list *begin_list2, int (*cmp)(void *, void *));
t_list				*ft_list_clone(t_list *begin_list);

// Loop on list

// Calls a given function for every element in a list
void				ft_list_foreach(t_list *begin_list, void (*f)(void *));
// Calls a given function for each list element that satisfies a given condition
void				ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
						void *data_ref, int (*cmp)(void *, void *));

// Conversion

// Converts an array of integers to a list
t_list				*ft_int_array_to_list(int *array, int size);
// Converts an array of strings to a list
t_list				*ft_strs_array_to_list(int size, char **strs);
// Converts a list of integers to an array
int					*ft_list_to_int_array(t_list *list);
// Converts a list of strings to an array
char				**ft_list_to_str_array(t_list *list);

// Display

// Prints a list of integers separated by a given string
void				ft_print_int_list(t_list *begin_list, char *sep);
// Prints a list of strings separated by a given string
void				ft_print_str_list(t_list *begin_list, char *sep);
// Reverse prints a list of integers separated by a given string
void				ft_print_int_list_reverse(t_list *begin_list, char *sep);

#endif
