#ifndef MINIRT_DEFS_BONUS_H
# define MINIRT_DEFS_BONUS_H

# include "ft_algebra.h"
# include "ft_list.h"

/* MACROS */

# define WIN_X 800
# define WIN_Y 800

# define RAY_REACH_MAX 1000
# define RAY_REACH_MIN 1e-4

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
	CONE,
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
	int				height;
}					t_img_data;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct s_material
{
	t_color			kd;
	t_color			ks;
	t_color			ka;
	double			specularity;
	t_img_data		img_texture;
}					t_material;

typedef struct s_triangle
{
	t_vector3d		a;
	t_vector3d		b;
	t_vector3d		c;
}					t_triangle;

typedef struct s_cone
{
	t_vector3d		pos;
	t_vector3d		axis;
	double			slope;
}					t_cone;

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
	t_vector3d		dir;
	t_vector3d		x_axis;
	t_vector3d		y_axis;
	double			fov_2;
}					t_camera;

typedef struct s_object
{
	enum e_object	type;
	unsigned int	index_mat;
	void			*object_r;
}					t_object;

typedef struct s_scene
{
	t_ambiant_light	a_light;
	t_camera		camera;
	t_point_light	p_light;
	t_list			*lights;
	t_list			*objects;
}					t_scene;

typedef struct s_ray
{
	t_vector3d		origin;
	t_vector3d		direction;
	t_color			color;
}					t_ray;

typedef struct s_intersection
{
	unsigned int	index_mat;
	t_vector3d		point;
	t_vector3d		normal;
	t_vector2d		uv;
}					t_intersection;

// State of the program
typedef struct s_state
{
	void			*display;
	void			*win;
	t_img_data		img_data;
	t_scene			scene;
	char			*id_list[3];
	t_material		*mats_tab;
	unsigned int	len_mats_tab;
}					t_state;

#endif
