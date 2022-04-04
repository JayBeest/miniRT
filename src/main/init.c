#include <libft.h>
#include <datatypes.h>
#include <main.h>
#include <parser_utils.h>
#include <shapes.h>

#include <stdio.h>

t_err	rt_mlx_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", TRUE);
	if (!mlx->mlx)
		return (MLX_INIT_F);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (MLX_NEW_IMG_F);
	return (NO_ERR);
}

void	init_temp_scene(t_minirt *rt)
{
	t_rt_shape	*node;

	rt->scene.origin = (t_vector){0, 0, 0};
	node = &rt->scene.shape;
	rt->scene.shapes = new_sphere(10, (t_vector){0, -10, 30}, (t_color){255, 0, 0, 255});
	rt->scene.shapes->next = new_sphere(10, (t_vector){20, 0, 40}, (t_color){0, 0, 255, 255});
	rt->scene.shapes->next->next = new_sphere(10, (t_vector){-20, 0, 4}, (t_color){0, 255, 0, 255});
	rt->scene.shapes->next->next->next = new_sphere(10, (t_vector){20, -20, 30}, (t_color){255, 255, 0, 255});
}

t_err	rt_init(t_minirt *rt)
{
	t_err	err;

	err = rt_mlx_init(&rt->mlx);
	rt->scene.resolution_x = WIDTH;
	rt->scene.resolution_y = HEIGHT;
	rt->scene.viewport_x = WIDTH / 2;
	rt->scene.viewport_y = HEIGHT / 2;
	rt->scene.d = 1;
	init_temp_scene(rt);

	return (err);
}
