/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bvh.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:21:56 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/09 15:24:57 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BVH_BONUS_H
# define MINIRT_BVH_BONUS_H

# include "minirt_defs.h"
# include <stdbool.h>

t_bvh		create_bvh(t_mesh *mesh);

t_aabb		create_aabb(const t_vec3 *vertices, t_bvh_elem *sub_elem);
double		intersect_aabb(t_ray ray, t_aabb box);

void		ft_vec3_to_array(t_vec3 v, double a[3]);
t_vec3		ft_array_to_vec3(const double a[3]);

// aabb_utils.c
bool		is_point_in_aabb(t_vec3 point, t_aabb box);
int			compare_aabb(void *a, void *b);
void		split_aabb(t_aabb box, t_aabb new[2]);

// bvh_free.c
void		free_triangle_obj(t_object *object);
void		free_bvh_elem(void *data);
void		free_node(t_bntree *node);

bool		triangle_aabb_overlap(unsigned int vertices_id[3], t_aabb box,
				const t_vec3 *vertices);

// bvh_triangle.c
t_bvh_tr	get_bvh_triangle(const t_vec3 *vertices, t_vertex *face, int index);
void		get_triangles_in_aabb(t_bvh_elem *parent_elem,
				t_bvh_elem *sub_elem);
void		get_vertices_in_aabb(t_bvh_elem *parent_elem, t_bvh_elem *sub_elem);

// to delete
void		print_aabb(t_aabb aabb);

#endif // !MINIRT_BVH_BONUS_H
