#ifndef MINIRT_DEFS_H
# define MINIRT_DEFS_H

# include "ft_algebra.h"

/* MACROS */

# define FALSE 0
# define TRUE 1

# define WIN_X 1600
# define WIN_Y 1000

/* ENUMS */

// Event codes
enum			e_event
{
	ON_KEYPRESS = 2,
	ON_CLIENTMSG = 33,
};

// Keyboard codes
enum			e_keycode
{
	K_ESC = 0xff1b,
};

/* STRUCTS */

// Data for an image buffer
typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bp_pixel;
	int			line_len;
	int			endian;
}				t_img_data;

typedef struct s_sphere
{
	t_vector3d	pos;
	double		diameter;
	t_vector3d	color;
}				t_sphere;

typedef struct s_plane
{
	t_vector3d	point;
	t_vector3d	normal;
	t_vector3d	color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector3d	pos;
	t_vector3d	axis;
	double		diameter;
	double		height;
	t_vector3d	color;
}				t_cylinder;

typedef struct s_ambient_light
{
	double		intensity;
	t_vector3d	color;
}				t_ambiant_light;

typedef struct s_point_light
{
	t_vector3d	pos;
	double		brightness;
	t_vector3d	color;
}				t_point_light;

typedef struct s_scene
{
	t_ambiant_light	a_light;
}				t_scene;

// State of the program
typedef struct s_state
{
	void		*display;
	void		*win;
	t_img_data	*img_data;
}				t_state;

#endif
