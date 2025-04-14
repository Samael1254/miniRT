/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_normals_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_NORMALS_BONUS_H
# define MINIRT_NORMALS_BONUS_H

# include "minirt_defs_bonus.h"

t_vec3	normal_at_point(t_object object, t_intersection inter, t_vec3 ray_dir);

// Object normal

t_vec3	sphere_normal(t_sphere sphere, t_vec3 point);
t_vec3	plane_normal(t_plane plane);
t_vec3	cone_normal(t_cone cone, t_vec3 point);
t_vec3	triangle_normal(t_triangle triangle, t_vec3 point);
t_vec3	cylinder_normal(t_cylinder cylinder, t_vec3 point);

#endif
