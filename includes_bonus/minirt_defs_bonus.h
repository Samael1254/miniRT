#ifndef MINIRT_DEFS_BONUS_H
# define MINIRT_DEFS_BONUS_H

# include "ft_algebra.h"
# include "ft_list.h"
# include <stdint.h>
# include <sys/time.h>

/* MACROS */

# define THREAD_COUNT sysconf(_SC_NPROCESSORS_ONLN)

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
	ESC_KEY = 0xff1b,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	Q_KEY = 113,
	E_KEY = 101,
	I_KEY = 0x069,
	J_KEY = 0x06a,
	K_KEY = 0x06b,
	L_KEY = 0x06c,
	UP_ARROW_KEY = 65362,
	DOWN_ARROW_KEY = 65364,
	LEFT_ARROW_KEY = 65361,
	RIGHT_ARROW_KEY = 65363,
	H_KEY = 0x0068,
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
	t_img_data		img_normal;
}					t_material;
# include "minirt_obj_parser.h"

typedef struct s_triangle
{
	t_mesh			*mesh;
	int				vertices[3];
	int				normals[3];
	int				uvs[3];
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
	unsigned char	move_step;
	unsigned char	rot_step;
}					t_camera;

typedef struct s_object
{
	enum e_object	type;
	unsigned int	index_mat;
	void			*object_r;
}					t_object;

typedef struct s_sky
{
	t_color	top;
	t_color	bottom;
}					t_sky;

typedef struct s_scene
{
	t_ambiant_light	a_light;
	t_camera		camera;
	t_point_light	p_light;
	t_sky			sky;
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
	char			*id_list[4];
	t_material		*mats_tab;
	unsigned int	len_mats_tab;
	struct timeval	start_time;
}					t_state;

typedef struct s_thread_data
{
	int				start_y;
	int				end_y;
	t_state			*state;
}					t_thread_data;

#endif
