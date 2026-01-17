/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_tree.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <gfulconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:29:17 by gfulconi          #+#    #+#             */
/*   Updated: 2025/03/05 13:29:17 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINARY_TREE_H
# define FT_BINARY_TREE_H

// Binary Tree structure
typedef struct s_bntree
{
	void			*data;
	struct s_bntree	*left;
	struct s_bntree	*right;
}					t_bntree;

// Creates a new tree node and sets its data
t_bntree			*ft_bntree_create_node(void *data);
// Frees a single tree node from memory
void				ft_bntree_delete_node(t_bntree *node,
						void (*free_fct)(void *));
// Clears a whole binary tree
void				ft_bntree_clear(t_bntree *root, void (*free_fct)(void *));

// Traverse the tree with the prefix method and apply a function to each node
void				ft_bntree_apply_prefix(t_bntree *root,
						void (*applyf)(void *));
// Traverse the tree with the infix method and apply a function to each node
void				ft_bntree_apply_infix(t_bntree *root,
						void (*applyf)(void *));
// Traverse the tree with the suffix method and apply a function to each node
void				ft_bntree_apply_suffix(t_bntree *root,
						void (*applyf)(void *));

// Inserts a new node inside a tree in a sorted manner
void				ft_bntree_insert(t_bntree *root, void *data,
						int (*cmpf)(void *, void *));
// Returns a pointer to the first element of the tree corresponding to
// the given one
void				*ft_bntree_search(t_bntree *root, void *data_ref,
						int (*cmpf)(void *, void *));

// Counts the depth of the tree
int					ft_bntree_level_count(t_bntree *root);

#endif
