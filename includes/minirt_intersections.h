/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_intersections.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:09 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:09 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_INTERSECTIONS_BONUS_H
# define MINIRT_INTERSECTIONS_BONUS_H

# include "minirt_defs.h"

t_intersection	intersect_scene(t_ray ray, t_state *state);

// Intersect objects

double			intersect_cone(t_ray ray, t_cone cone);
double			intersect_sphere(t_ray ray, t_sphere sphere);
double			intersect_plane(t_ray ray, t_plane plane);
double			intersect_cylinder(t_ray ray, t_cylinder cylinder);
double			intersect_triangle(t_ray ray, t_bvh_tr triangle,
					const t_vec3 *vertices);
double			intersect_mesh(t_ray ray, t_mesh *mesh,
					t_object **triangle_obj);

// Intersections utils

double			closest_root(double root1, double root2);
double			triangle_distance(double d, t_ray ray, t_vec3 vectors[3],
					t_vec3 a);
double			cone_delta(double params[3], t_vec3 co, t_ray ray, t_cone cone);
double			cylinder_delta(t_ray ray, t_cylinder cylinder, double params[5],
					t_vec3 vectors[3]);
double			intersect_cap(t_ray ray, t_cylinder cylinder, bool top);
double			intersect_cylinder_body(t_ray ray, t_cylinder cylinder);

#endif
