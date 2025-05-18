/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parsing.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/05/18 16:55:32 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PARSING_BONUS_H
# define MINIRT_PARSING_BONUS_H

# include "minirt_defs.h"
# include <stdbool.h>

// create_light.c
void		add_lights_to_list(t_state *state, char **split);

// init_scene.c
void		init_scene(t_state *state, char *filename);

// insert_in_struct.c
void		add_light(t_state *state, char **split);
int			insert_in_struct(t_state *state, char **split);

// object_cone.c
t_object	*object_cone(t_state *state, char **split);

// object_cylinder.c
t_object	*object_cylinder(t_state *state, char **split);

// object_mesh.c
t_object	*object_mesh(t_state *state, char **split);

// object_plane.c
t_object	*object_plane(t_state *state, char **split);

// object_sphere.c
t_object	*object_sphere(t_state *state, char **split);

// objects_list.c
void		add_object_to_list(t_state *state, char **split);

// open_and_count_mats.c
int			open_and_count_mats(t_state *state, char *filename);

// utils2.c
void		check_line(t_state *state, char **split, int split_len);
bool		is_vec3_in_range(t_vec3 vec, double min, double max);
bool		ft_check_error_line(char **split, int len);
bool		ft_check_split_data(char **split);

// utils.c
t_color		get_color(char *line_color, bool *error);
t_vec3		get_vector(char *line_vector, bool *error);

// utils_general_objects.c
void		ambiant_light_checker(t_state *state, char **split);

// utils_mat.c
void		init_mat(t_material *mat, char **line_mat, bool *has_error);
bool		get_texture_map_img(t_state *state, char *filename,
				t_material *mat);
bool		get_normal_map_img(t_state *state, char *filename, t_material *mat);

#endif // !MINIRT_PARSING_BONUS_H
