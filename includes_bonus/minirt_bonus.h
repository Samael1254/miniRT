#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "minirt_defs_bonus.h"
# include <stdbool.h>

// Init state //

// Initializes the program state
void			init_state(t_state *state, char *filename);
void			init_scene(t_state *state, char *filename);
int				insert_in_struct(t_state *state, char **split);

// Time //

struct timeval	get_time(t_state *state);
long			get_time_diff(struct timeval time, struct timeval start_time);

// Parsing

// utils.c
t_vector3d		get_vector(char *line_vector, bool *error);
t_color			get_color(char *line_color, bool *error);
bool			is_vector3d_in_range(t_vector3d vec, double min, double max);
bool			is_t_color_valid(t_color color, double min, double max);
bool			is_norm_vector_valid(t_vector3d vec);

// utils2.c
bool			ft_check_error_line(char **split, int len);
bool			ft_check_split_data(char **split);
void			check_line(t_state *state, char **split, int split_len);

// utils_general_objects.c
void			ambiant_light_checker(t_state *state, char **split);

// objects_list.c
void			add_object_to_list(t_state *state, char **split);

// objects*.c
t_object		*object_sphere(t_state *state, char **split);
t_object		*object_plane(t_state *state, char **split);
t_object		*object_cylinder(t_state *state, char **split);
t_object		*object_cone(t_state *state, char **split);
t_object		*object_mesh(t_state *state, char **split);

// create_lights_bonus.c
void			add_lights_to_list(t_state *state, char **split);

// open_and_counts_mats_bonus.c
int				open_and_count_mats(t_state *state, char *filename);

// utils_mats.c
void			get_normal_map_img(t_state *state, char *filename,
					t_material *mat);
void			get_texture_map_img(t_state *state, char *filename,
					t_material *mat);

// Events //

// Loops while waiting for events
void			loop_events(t_state *state);
void			modify_rot_step_size(t_state *state, char sign);
void			modify_step_size(t_state *state, char sign);

// Transform //

void			transform_scene(t_scene *scene);

// Ray tracing //

void			ray_tracing(t_state *state);

// Rays //

void			shoot_rays(t_state *state);

// Intersections //

double			intersect_sphere(t_ray ray, t_sphere sphere);
double			intersect_plane(t_ray ray, t_plane plane);
double			intersect_cylinder(t_ray ray, t_cylinder cylinder);
double			intersect_cone(t_ray ray, t_cone cone);
double			intersect_mesh(t_ray ray, t_mesh *mesh,
					t_object **triangle_obj);
t_intersection	intersect_scene(t_ray ray, t_state *state);

t_vector3d		normal_at_point(t_object object, t_intersection inter,
					t_vector3d ray_dir);
t_vector3d		blend_normal_map(t_vector2d uv, t_vector3d normal,
					t_material material);

t_vector2d		uv_at_point(t_object object, t_vector3d point,
					t_vector3d normal);

t_vector3d		get_reference_vector(t_vector3d normal);
t_vector2d		clamp_uv(t_vector2d uv);
t_vector3d		interpolate_triangle_data3d(t_vector3d vertices[3],
					t_vector3d point, t_vector3d data[3]);
t_vector2d		interpolate_triangle_data2d(t_vector3d vertices[3],
					t_vector3d point, t_vector2d data[3]);

// Light //

t_color			phong_illumination(t_state *state, t_intersection inter,
					t_ray ray);

// Graphics //

t_color			add_colors(t_color color1, t_color color2);
t_color			scale_color(t_color color, double lambda);
t_color			init_color(unsigned char r, unsigned char g, unsigned char b);
t_color			absorb_colors(t_color color1, t_color color2);
t_color			get_sky_color(t_sky sky, t_ray ray);
t_color			get_pixel_color(t_img_data texture, t_vector2d uv);
void			render_scene(t_state *state, t_ray **rays);
void			put_pixel(t_img_data *img, t_ivector2d coords, t_color color);

// Check arguments //

// Checks if the program arguments are valid
void			check_arguments(int argc, char **argv);

// Errors //

unsigned int	warnings_number(bool add);
void			warning(char const *type, char const *msg);
void			info(char const *type, char const *msg);
// Prints an error and exits the program
void			error(char const *type, char const *msg, t_state *state);

// Exit program //

// Frees the program state and exits the program
int				exit_program(t_state *state, int status);

// PRINT FOR DEBUGS
void			print_scene(t_scene scene);
void			print_vector3d(t_vector3d vec);
void			print_color(t_color color);

#endif
