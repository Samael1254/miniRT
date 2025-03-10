#include "ft_algebra.h"
#include "ft_math.h"
#include "minirt.h"
#include "minirt_defs.h"
#include <stdbool.h>

// void	shade_color(t_color *color, t_scene *scene, bool in_shadow)
// {
// 	if (in_shadow)
// 	{
// 		*color = apply_brightness(*color, scene->a_light.brightness);
// 		*color = average_colors(*color, scene->a_light.color);
// 	}
// 	else
// 	{
// 		*color = apply_brightness(*color, ft_maxf(scene->p_light.brightness,
// 					scene->a_light.brightness));
// 		*color = average_colors(*color, scene->p_light.color);
// 	}
// }

// static void	direct_rays_to_light(t_ray **rays, t_point_light light)
// {
// 	t_ivector2d	coords;
// 	t_vector3d	light_dir;
//
// 	coords.y = 0;
// 	while (coords.y < WIN_Y)
// 	{
// 		coords.x = 0;
// 		while (coords.x < WIN_X)
// 		{
// 			light_dir = ft_normalize_vector3d(ft_sub_vectors3d(light.pos,
// 						rays[coords.y][coords.x].origin));
// 			rays[coords.y][coords.x].direction = light_dir;
// 			coords.x++;
// 		}
// 		coords.y++;
// 	}
// }

// static void	shoot_rays_to_light(t_ray **rays, t_state *state)
// {
// 	t_ivector2d	coords;
// 	bool		in_shadow;
// 	t_ray		ray_inter;
//
// 	coords.y = 0;
// 	while (coords.y < WIN_Y)
// 	{
// 		coords.x = 0;
// 		while (coords.x < WIN_X)
// 		{
// 			ray_inter = intersect_scene(rays[coords.y][coords.x],
// 					state->scene.objects);
// 			in_shadow = ft_distance3d(rays[coords.y][coords.x].origin,
// 					state->scene.p_light.pos) >= ft_distance3d(rays[coords.y][coords.x].origin,
// 					ray_inter.origin);
// 			shade_color(&rays[coords.y][coords.x].color, &state->scene,
// 				in_shadow);
// 			coords.x++;
// 		}
// 		coords.y++;
// 	}
// }

// void	light_scene(t_ray **rays, t_state *state)
// {
// 	direct_rays_to_light(rays, state->scene.p_light);
// 	shoot_rays_to_light(rays, state);
// }

static t_vector3d	light_direction(t_ray ray, t_point_light light)
{
	t_vector3d	light_dir;

	light_dir = ft_normalize_vector3d(ft_sub_vectors3d(light.pos, ray.origin));
	return (light_dir);
}

static t_color	shade_material(t_color color, double brightness,
		t_color light_color)
{
	t_color	lit_color;

	lit_color = apply_brightness(color, brightness);
	lit_color = average_colors(lit_color, light_color);
	return (lit_color);
}

t_color	shade_ray(t_intersection inter, t_scene *scene)
{
	t_ray			light_ray;
	t_intersection	light_inter;
	bool			in_shadow;

	light_ray.origin = inter.point;
	light_ray.direction = light_direction(light_ray, scene->p_light);
	light_inter = intersect_scene(light_ray, scene->objects);
	in_shadow = ft_distance3d(light_ray.origin,
			scene->p_light.pos) >= ft_distance3d(light_ray.origin,
			light_inter.point);
	if (in_shadow)
		return (shade_material(inter.color, scene->a_light.brightness,
				scene->a_light.color));
	return (shade_material(inter.color, ft_maxf(scene->p_light.brightness,
				scene->a_light.brightness), scene->p_light.color));
}
