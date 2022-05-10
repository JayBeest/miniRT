/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   datatypes.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:12 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 18:53:02 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

# include <MLX42.h>
# include <ansi_color_codes.h>

# define WIDTH 768
# define HEIGHT 768
# define USLEEP_FPS 16666

# define T_MAX 100000
# define EPSILON 1e-6

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef enum e_parse_type
{
	A,
	C,
	L,
	SP,
	PL,
	CY
}		t_parse_type;

typedef enum e_err
{
	NO_ERR,
	MALLOC_F,
	MLX_INIT_F,
	MLX_NEW_IMG_F,
	PARSE_F,
	INVALID_ARG,
	INVALID_FILE,
	INVALID_OBJ,
	PIXEL_OOB
}		t_err;

typedef struct s_quad_abc
{
	double	a;
	double	b;
	double	c;
}		t_quad_abc;

typedef	struct s_quad_result
{
	double	t1;
	double	t2;
}		t_quad_result;

typedef enum e_rt_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	CUBE,
	DIRECT_L,
	POINT_L,
	NO_OBJECT
}		t_rt_shape_type;

typedef struct s_color
{
	unsigned char 	r;
	unsigned char 	g;
	unsigned char 	b;
	unsigned char 	a;
}			t_color;

typedef struct s_color_intensity
{
	double	r;
	double	g;
	double	b;
	double	a;
}			t_color_intensity;

typedef struct s_pixel
{
	int 	x;
	int 	y;
	t_color	color;
}			t_pixel;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_position
{
	double	x;
	double	y;
	double	z;
}			t_position;

typedef struct s_rt_shape
{
	int					id;
	t_rt_shape_type		type;
	int 				fov;
	double				ratio;
	double				size;
	int					radius;
	t_color				color;
	int 				specular;
	t_vector			vector;
	t_vector			pos1;
	t_vector			pos2;
	t_vector			pos3;
	struct s_rt_shape	*next;
}		t_rt_shape;

typedef struct s_intersect_result
{
	t_rt_shape	*closest_shape;
	double		closest_t;

}		t_intersect_result;

typedef struct s_scene
{
	int 		resolution_x;
	int 		resolution_y;
	int			viewport_x;
	int			viewport_y;
	int 		d;
	t_vector	origin;
	t_rt_shape	ambient_light;
	t_rt_shape	*cameras;
	t_rt_shape	*lights;
	t_rt_shape	*shapes;
}		t_scene;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t *text;
}		t_mlx;

typedef struct s_minirt
{
	t_mlx	mlx;
	t_scene	scene;
}		t_minirt;

typedef struct s_mult_pixel
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}		t_mult_pixel;

typedef struct s_multipt
{
	t_minirt	*rt;
	int 		id;
}		t_pthr_arg;

#endif