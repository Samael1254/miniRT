#ifndef MINIRT_DEFS_H
# define MINIRT_DEFS_H

# include "ft_algebra.h"
# include "ft_list.h"

/* MACROS */

# define FALSE 0
# define TRUE 1

# define WIN_X 1600
# define WIN_Y 1000

/* ENUMS */

// Event codes
enum				e_event
{
	ON_KEYPRESS = 2,
	ON_CLIENTMSG = 33,
};

// Keyboard codes
enum				e_keycode
{
	K_ESC = 0xff1b,
};

enum				e_light
{
	L_POINT,
	L_AMBIANT,
};

enum				e_object
{
	SPHERE,
	PLANE,
	CYLINDER,
};

/* STRUCTS */

// Data for an image buffer
typedef struct s_img_data
{
	void			*img;
	char			*addr;
	int				bp_pixel;
	int				line_len;
	int				endian;
}					t_img_data;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct s_sphere
{
	t_vector3d		pos;
	double			diameter;
}					t_sphere;

typedef struct s_plane
{
	t_vector3d		point;
	t_vector3d		normal;
}					t_plane;

typedef struct s_cylinder
{
	t_vector3d		pos;
	t_vector3d		axis;
	double			diameter;
	double			height;
}					t_cylinder;

typedef struct s_ambient_light
{
	double			brightness;
	t_color			color;
}					t_ambiant_light;

typedef struct s_point_light
{
	t_vector3d		pos;
	double			brightness;
	t_color			color;
}					t_point_light;

typedef struct s_camera
{
	t_vector3d		pos;
	t_vector3d		rot;
	int				fov;
}					t_camera;

typedef struct s_object
{
	enum e_object	type;
	t_color			color;
	void			*object_r;
}					t_object;

typedef struct s_scene
{
	t_ambiant_light	a_light;
	t_camera		camera;
	t_point_light	p_light;
	t_list			*objects;
}					t_scene;

typedef struct s_ray
{
	t_vector3d		origin;
	t_vector3d		direction;
}					t_ray;

typedef struct s_intersection
{
	t_vector3d		point;
	t_color			color;
}					t_intersection;

// State of the program
typedef struct s_state
{
	void			*display;
	void			*win;
	t_img_data		img_data;
	t_scene			scene;
}					t_state;

#endif
