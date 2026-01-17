/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algebra.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfulconi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:27:40 by gfulconi          #+#    #+#             */
/*   Updated: 2025/05/25 14:05:19 by gfulconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALGEBRA_H
# define FT_ALGEBRA_H

typedef enum e_axis
{
	X_AXIS = 0,
	Y_AXIS = 1,
	Z_AXIS = 2,
}				t_axis;

// 2d integer vector
typedef struct s_ivec2
{
	int			x;
	int			y;
}				t_ivec2;

// 2d double vector
typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

// 3d double vector
typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

// 4d double vector
typedef struct s_vec4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4;

typedef t_vec2	t_point2;

typedef t_vec3	t_point3;

// ADD

// Computes the sum of two 2d vectors
t_vec2			ft_add_vec2(t_vec2 a, t_vec2 b);
// Computes the sum of two 3d vectors
t_vec3			ft_add_vec3(t_vec3 a, t_vec3 b);
// Computes the sum of two 4d vectors
t_vec4			ft_add_vec4(t_vec4 a, t_vec4 b);

// SUB

// Computes the difference of two 2d vectors
t_vec2			ft_sub_vec2(t_vec2 a, t_vec2 b);
// Computes the difference of two 3d vectors
t_vec3			ft_sub_vec3(t_vec3 a, t_vec3 b);
// Computes the difference of two 4d vectors
t_vec4			ft_sub_vec4(t_vec4 a, t_vec4 b);

// SCALE

// Computes the scaling of a 2d vector by lambda
t_vec2			ft_scale_vec2(double lambda, t_vec2 a);
// Computes the scaling of a 3d vector by lambda
t_vec3			ft_scale_vec3(double lambda, t_vec3 a);
// Computes the scaling of a 4d vector by lambda
t_vec4			ft_scale_vec4(double lambda, t_vec4 a);

// NORM

// Computes the norm of a 2d vector
double			ft_vec2_norm(t_vec2 a);
// Computes the norm of a 3d vector
double			ft_vec3_norm(t_vec3 a);

// Computes the square norm of a 2d vector
double			ft_vec2_square_norm(t_vec2 a);
// Computes the square norm of a 3d vector
double			ft_vec3_square_norm(t_vec3 a);

// NORMALIZE

// Returns a normalized version (of norm 1) of a 2d vector
t_vec2			ft_normalize_vec2(t_vec2 a);
// Returns a normalized version (of norm 1) of a 3d vector
t_vec3			ft_normalize_vec3(t_vec3 a);

// DOT PRODUCT

// Computes the dot product of two 2d vectors
double			ft_dot_vec2(t_vec2 a, t_vec2 b);
// Computes the dot product of two 3d vectors
double			ft_dot_vec3(t_vec3 a, t_vec3 b);

// CROSS PRODUCT

// Computes the cross product of two 3d vectors
t_vec3			ft_cross_vec3(t_vec3 a, t_vec3 b);

// DISTANCE BETWEEN TWO POINTS

// Computes the distance between two 2d vectors
double			ft_distance2d(t_vec2 a, t_vec2 b);
// Computes the distance between two 3d vectors
double			ft_distance3d(t_vec3 a, t_vec3 b);

// MIDDLE OF TWO POINTS

// Returns the middle between two 2d vectors
t_vec2			ft_middle2d(t_vec2 a, t_vec2 b);
// Returns the middle between two 3d vectors
t_vec3			ft_middle3d(t_vec3 a, t_vec3 b);

// LINEAR INTERPOLATION

// Returns a linear interpolation between two 2d vectors
t_vec2			ft_lerp2d(t_vec2 a, t_vec2 b, double lambda);
// Returns a linear interpolation between two 3d vectors
t_vec3			ft_lerp3d(t_vec3 a, t_vec3 b, double lambda);

// ANGLES BETWEEN VECTORS

// Computes the angle formed by two 2d vectors
double			ft_vec2_angle(t_vec2 a, t_vec2 b);
// Computes the angle formed by two 3d vectors
double			ft_vec3_angle(t_vec3 a, t_vec3 b);

// ANGLE CONVERSION

// Converts an angle from radians to degrees
double			ft_rad_to_deg(double rad);
// Converts an angle from degress to radians
double			ft_deg_to_rad(double deg);

// CHECK ORTHOGONALITY

// Checks whether two 2d vectors are orthogonal
int				ft_are_vec2_ortho(t_vec2 a, t_vec2 b);
// Checks whether two 3d vectors are orthogonal
int				ft_are_vec3_ortho(t_vec3 a, t_vec3 b);

// CHECK COLINEARITY

// Checks whether two 2d vectors are colinear
int				ft_are_vec2_col(t_vec2 a, t_vec2 b);
// Checks whether two 3d vectors are colinear
int				ft_are_vec3_col(t_vec3 a, t_vec3 b);

// 2d LINE EQUATION

// Returns the equation of a 2d line passing through two points in the form
// of a 3d vector
t_vec3			ft_line2d_equation(t_vec2 a, t_vec2 b);

// 2d LINE DIRECTION VECTOR

// Returns the direction vector of a 2d line
t_vec2			ft_direction_vec2(t_vec3 line);

// 2d LINES INTERSECTION

// Returns the intersection point between two 2d lines
t_vec2			ft_lines2d_intersection(t_vec3 l1, t_vec3 l2);

// VECTOR CONVERSION

// Converts a 3d vector to 2d
t_vec2			ft_3to2_vec(t_vec3 v3);
// Converts a 4d vector to 3d
t_vec3			ft_4to3_vec(t_vec4 v4);
// Converts a 3d vector to 4d
t_vec4			ft_3to4_vec(t_vec3 v3);
// Converts a 2d vector to 3d
t_vec3			ft_2to3_vec(t_vec2 v2);
// Converts a 2d integer vector to double
t_vec2			ft_i2to2_vec(t_ivec2 vi2);

// SET VECTOR

// Returns a 2d integer vector with the given coordinates
t_ivec2			ft_set_ivec2(int x, int y);
// Returns a 2d vector with the given coordinates
t_vec2			ft_set_vec2(double x, double y);
// Returns a 3d vector with the given coordinates
t_vec3			ft_set_vec3(double x, double y, double z);
// Returns a 4d vector with the given coordinates
t_vec4			ft_set_vec4(double x, double y, double z, double w);

// INIT VECTOR

// Returns a 2d vector with all coordinates set to the given value
t_vec2			ft_init_vec2(double value);
// Returns a 3d vector with all coordinates set to the given value
t_vec3			ft_init_vec3(double value);
// Returns a 4d vector with all coordinates set to the given value
t_vec4			ft_init_vec4(double value);

// ROTATE VECTOR

// Returns the given 3d vector (2d homogeneous vector) rotated by the given
// rotator (containing the rotation angles along each two axes)
t_vec3			ft_rotate_vec3(t_vec3 v, t_vec2 rotator);
// Returns the given 4d vector (3d homogeneous vector) rotated by the given
// rotator (containing the rotation angles along all axes)
t_vec4			ft_rotate_vec4(t_vec4 v, t_vec3 rotator);

// TRANSLATE VECTOR

// Returns the given translated 3d vector (2d homogeneous vector) along each
// two axes by the coordinates of the given translator
t_vec3			ft_translate_vec3(t_vec3 v, t_vec2 translator);
// Returns the given translated 4d vector (3d homogeneous vector) along each
// two axes by the coordinates of the given translator
t_vec4			ft_translate_vec4(t_vec4 v, t_vec3 translator);

// GET BASE VECTOR

// Returns the 2d base vector corresponding to the given axis
t_vec2			ft_get_base_vec2(t_axis axis);
// Returns the 3d base vector corresponding to the given axis
t_vec3			ft_get_base_vec3(t_axis axis);
// Returns the 4d base vector corresponding to the given axis
t_vec4			ft_get_base_vec4(t_axis axis);

// SET NULL MATRIX

// Sets all the elements of a given 2d matrix to zero
void			ft_set_null_mat2(double m[2][2]);
// Sets all the elements of a given 3d matrix to zero
void			ft_set_null_mat3(double m[3][3]);
// Sets all the elements of a given 4d matrix to zero
void			ft_set_null_mat4(double m[4][4]);

// ADD MATRIXES

// Stores the sum of two given 3d matrixes in a third matrix
void			ft_add_mat3(double a[3][3], double b[3][3], double sum[3][3]);
// Stores the sum of two given 4d matrixes in a third matrix
void			ft_add_mat4(double a[4][4], double b[4][4], double sum[4][4]);

// SCALE MATRIXES

// Scales the given 3d matrix by a factor lambda
void			ft_scale_mat3(double m[3][3], double lambda);
// Scales the given 4d matrix by a factor lambda
void			ft_scale_mat4(double m[4][4], double lambda);

// MATRIX PRODUCT

// Stores the product of two given 3d matrixes in a third matrix
void			ft_mat3_product(double a[3][3], double b[3][3],
					double prod[3][3]);
// Stores the product of two given 4d matrixes in a third matrix
void			ft_mat4_product(double a[4][4], double b[4][4],
					double prod[4][4]);

// MATRIX VECTOR PRODUCT

// Returns the result of a 3d matrix-vector product in a 3d vector
t_vec3			ft_mat_vec_product3(double m[3][3], t_vec3 v);
// Returns the result of a 4d matrix-vector product in a 4d vector
t_vec4			ft_mat_vec_product4(double m[4][4], t_vec4 v);

// MATRIX CONVERSION

// Converts a 3d matrix to 4d and sets the new coefficients to 0
void			ft_3to4_mat(double m3[3][3], double m4[4][4]);
// Converts a 4d matrix to 3d
void			ft_4to3_mat(double m4[4][4], double m3[3][3]);

// TRANSLATION MATRIX

// Stores a 3d translation matrix from the given translator
void			ft_set_translation_mat3(double m[3][3], t_vec2 t);
// Stores a 4d translation matrix from the given translator
void			ft_set_translation_mat4(double m[4][4], t_vec3 t);

// ROTATION MATRIX

void			ft_set_base_rotation_mat3(double m[3][3], double angle,
					t_axis axis);
void			ft_set_base_rotation_mat4(double m[4][4], double angle,
					t_axis axis);
void			ft_set_rotation_mat3(double m[3][3], double angle, t_vec3 axis);
void			ft_set_rotation_mat4(double m[4][4], double angle, t_vec3 axis);

// STRETCHING MATRIX

void			ft_set_stretching_mat3(double m[3][3], t_vec3 s);
void			ft_set_stretching_mat4(double m[4][4], t_vec4 s);

// SCALING MATRIX

void			ft_set_scaling_mat3(double m[3][3], double s);
void			ft_set_scaling_mat4(double m[4][4], double s);

// ORTHOGRAPHIC PROJECTION

t_vec3			ft_orthographic_projection(t_vec4 v);

// AXONOMETRIC PROJECTIONS

t_vec3			ft_axonometric_projection(t_vec4 v, double ang1, double ang2);
t_vec3			ft_dimetric_projection(t_vec4 v, double ang1);
t_vec3			ft_isometric_projection(t_vec4 v);

// OBLIQUE PROJECTION

t_vec3			ft_oblique_projection(t_vec4 v, double depth, double angle);
t_vec3			ft_cavalier_projection(t_vec4 v);
t_vec3			ft_cabinet_projection(t_vec4 v);

// PLANE PROJECTION

t_vec3			ft_plane_projection(t_vec4 v, t_axis normal);

// 1-POINT PERSPECTIVE PROJECTION

t_vec3			ft_perspective_projection(t_vec4 v, t_vec4 cam_pos,
					t_vec3 cam_rot, t_ivec2 display_size);

// MATRIX DETERMINANT

// Compute the determinant of a 2d matrix
int				ft_determinant2d(double m[2][2]);

// REFLEXION MATRIX

// SHEERING MATRIX

// 3d LINE EQUATION

// PLANE EQUATION

// 3d LINE / PLANE INTERSECTION

// PLANE / PLANE INTERSECTION

// CIRCLE EQUATION

// SPHERE EQUATION

// MATRIX TRACE

// EIGENVALUES AND EIGENVECTORS

// TRANSPOSED MATRIX

// INVERSE MATRIX

// PRINT VECTOR

void			ft_print_vec2(t_vec2 v, int precision);
void			ft_print_vec3(t_vec3 v, int precision);
void			ft_print_vec4(t_vec4 v, int precision);

// PRINT MATRIX

void			ft_print_mat3(double m[3][3], int precision);
void			ft_print_mat4(double m[4][4], int precision);

#endif
