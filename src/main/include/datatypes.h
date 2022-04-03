#ifndef DATATYPES_H
# define DATATYPES_H

# include <MLX42.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;


typedef enum e_err
{
	NO_ERR,
	MALLOC_F,
	MLX_INIT_F,
	MLX_NEW_IMG_F,
	INVALID_ARG,
	INVALID_FILE,
	PIXEL_OOB
}		t_err;

typedef struct s_quad_abc
{
	int	a;
	int	b;
	int	c;
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
	NO_OBJECT
}		t_rt_shape_type;

typedef struct s_color
{
	unsigned char 	r;
	unsigned char 	g;
	unsigned char 	b;
	unsigned char 	a;
}			t_color;

typedef struct s_pixel
{
	int 	x;
	int 	y;
	t_color	color;
}			t_pixel;

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}			t_vector;

typedef struct s_position
{
	int	x;
	int	y;
	int	z;
}			t_position;

typedef struct s_rt_shape
{
	int					id;
	t_rt_shape_type	type;
	int 				fov;
	double				ratio;
	double				size;
	int					radius;
	t_color				color;
	t_vector			vector;
	t_position			pos1;
	t_position			pos2;
	t_position			pos3;
	struct s_rt_shape	*next;
}		t_rt_shape;

typedef struct s_scene
{
	int 		resolution_x;
	int 		resolution_y;
	int			viewport_x;
	int			viewport_y;
	int 		d;
	t_vector	origin;
	t_rt_shape	ambient_ligth;
	t_rt_shape	*cameras;
	t_rt_shape	*lights;
	t_rt_shape	*shapes;
}		t_scene;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}		t_mlx;

typedef struct s_minirt
{
	t_mlx	mlx;
	t_scene	scene;
}		t_minirt;

#endif