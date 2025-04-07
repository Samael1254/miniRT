/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bvh_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:21:56 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/07 15:55:09 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BVH_BONUS_H
# define MINIRT_BVH_BONUS_H

# include "minirt_defs_bonus.h"
# include <stdbool.h>

t_bvh		create_bvh(t_mesh *mesh);

t_aabb		create_aabb(const t_vec3 *vertices, t_bvh_elem *sub_elem);
double		intersect_aabb(t_ray ray, t_aabb box);

void		ft_vec3_to_array(t_vec3 v, double a[3]);
t_vec3		ft_array_to_vec3(const double a[3]);

// aabb_utils_bonus.c
bool		is_point_in_aabb(t_vec3 point, t_aabb box);
int			compare_aabb(void *a, void *b);
void		split_aabb(t_aabb box, t_aabb new[2]);

// bvh_free_bonus.c
void		free_bvh_elem(t_bvh_elem *elem);
void		free_node(t_bntree *node);

bool		triangle_aabb_overlap(unsigned int vertices_id[3], t_aabb box,
				const t_vec3 *vertices);

// bvh_triangle_bonus.c
t_bvh_tr	get_bvh_triangle(const t_vec3 *vertices, t_vertex *face, int index);
void		get_triangles_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem,
				const t_vec3 *vertices);
void		get_vertices_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem);

// to delete
void		print_aabb(t_aabb aabb);

#endif // !MINIRT_BVH_BONUS_H
