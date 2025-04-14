/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_transform_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuesta <macuesta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:29 by macuesta          #+#    #+#             */
/*   Updated: 2025/04/14 17:21:29 by macuesta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TRANSFORM_BONUS_H
# define MINIRT_TRANSFORM_BONUS_H

# include "minirt_defs_bonus.h"

t_vec3		world_to_view(t_vec3 vect, t_camera camera);
void		transform_point_light(t_point_light *light, t_camera camera);
void		transform_object(t_object *object, t_camera camera);

#endif
