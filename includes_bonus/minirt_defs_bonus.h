#ifndef MINIRT_DEFS_BONUS_H
# define MINIRT_DEFS_BONUS_H

# include "ft_algebra.h"
# include "ft_binary_tree.h"
# include "ft_list.h"
# include <stdbool.h>
# include <sys/time.h>

/* MACROS */

# define THREAD_COUNT 20

# define ID_LIST_SIZE 4

# define BVH_DEPTH 8
# define BVH_MIN_TRIANGLES 5

# define WIN_X 800
# define WIN_Y 800

# define RAY_REACH_MAX 1000
# define RAY_REACH_MIN 1e-4
# define BOUNCE_MAX 10

# define AIR_REFRACTION 1.000293

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
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
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
	F_KEY = 0x066,
	UP_ARROW_KEY = 65362,
	DOWN_ARROW_KEY = 65364,
	LEFT_ARROW_KEY = 65361,
	RIGHT_ARROW_KEY = 65363,
	ALT_KEY = 65513,
	H_KEY = 0x0068,
};

enum				e_mat_param
{
	M_ID,
	M_KD,
	M_KS,
	M_KA,
	M_SPEC,
	M_REFL,
	M_TRANS,
	M_REFR,
	M_TX,
	M_NM
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
	MESH,
	TRIANGLE,
	AABB,
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
	unsigned char	a;
}					t_color;

typedef struct s_material
{
	t_color			kd;
	t_color			ks;
	t_color			ka;
	double			specularity;
	double			reflectance;
	double			transparency;
	double			refraction;
	t_img_data		img_texture;
	t_img_data		img_normal;
}					t_material;

typedef struct s_aabb
{
	t_vec3			min;
	t_vec3			max;
}					t_aabb;

typedef struct s_bvh_tr
{
	unsigned int	id;
	unsigned int	vertices_id[3];
	t_vec3			centroid;
}					t_bvh_tr;

typedef struct s_bvh_elem
{
	t_aabb			box;
	t_bvh_tr		*triangles;
	unsigned int	n_triangles;

}					t_bvh_elem;

typedef struct s_bvh
{
	t_bntree		*root;
}					t_bvh;

typedef struct vertex
{
	int				geo_id;
	int				text_id;
	int				norm_id;
}					t_vertex;

typedef struct s_triangle
{
	t_vec3			vertices[3];
	t_vec3			normals[3];
	t_vec2			uvs[3];
}					t_triangle;

typedef struct s_mesh
{
	t_vec3			*vertices;
	int				n_vertices;
	t_vec3			*normals;
	int				n_normals;
	t_vec2			*uvs;
	int				n_uvs;
	t_vertex		**faces;
	int				n_faces;
	t_bvh			bvh;
}					t_mesh;

typedef struct s_cone
{
	t_vec3			pos;
	t_vec3			axis;
	double			slope;
}					t_cone;

typedef struct s_sphere
{
	t_vec3			pos;
	double			diameter;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			axis;
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
	t_vec3			pos;
	double			brightness;
	t_color			color;
}					t_point_light;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			x_axis;
	t_vec3			y_axis;
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
	t_color			top;
	t_color			bottom;
}					t_sky;

typedef struct s_scene
{
	t_ambiant_light	a_light;
	t_camera		camera;
	t_sky			sky;
	t_list			*lights;
	t_list			*objects;
}					t_scene;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
	double			refraction;
}					t_ray;

typedef struct s_intersection
{
	unsigned int	index_mat;
	unsigned int	bounces;
	t_vec3			point;
	t_vec3			normal;
	t_vec2			uv;
}					t_intersection;

// State of the program
typedef struct s_state
{
	void			*display;
	void			*win;
	t_img_data		img_data;
	t_scene			scene;
	char			*id_list[ID_LIST_SIZE];
	t_material		*mats_tab;
	unsigned int	len_mats_tab;
	struct timeval	start_time;
	struct timeval	end_time;
	unsigned char	hold_alt;
	bool			toggle_lights;
	bool			toggle_fps;
	bool			toggle_help;
}					t_state;

typedef struct s_thread_data
{
	int				start_y;
	int				end_y;
	t_state			*state;
}					t_thread_data;

#endif
