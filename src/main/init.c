#include <libft.h>
#include <datatypes.h>
#include <main.h>
#include <parser_utils.h>
#include <shapes.h>
#include <lights.h>

#include <stdio.h>

t_err	rt_mlx_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", TRUE);
	if (!mlx->mlx)
		return (MLX_INIT_F);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (MLX_NEW_IMG_F);
	mlx->text = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->text)
		return (MLX_NEW_IMG_F);
	return (NO_ERR);
}

void	init_temp_scene(t_minirt *rt)
{
	t_rt_shape	*node;

	rt->scene.origin = (t_vector){0, 0, 0};
	rt->scene.shapes = new_sphere(250, (t_vector){0, -100, 800}, (t_color){255, 0, 0, 255});//RED
	rt->scene.shapes->next = new_sphere(250, (t_vector){200, 0, 900}, (t_color){0, 0, 255, 255});//BLUE
	rt->scene.shapes->next->next = new_sphere(600, (t_vector){-300, -200, 1250}, (t_color){0, 255, 0, 255});//GREEN
	rt->scene.shapes->next->next->next = new_sphere(350, (t_vector){250, -350, 900}, (t_color){255, 255, 0, 255});//YELLOW

	rt->scene.ambient_ligth = new_ambient_light(1.124, (t_color){255 ,255 ,255 ,255});
	rt->scene.lights = new_point_light(1, (t_position){-50, -180, 100}, (t_color){255 ,255 ,255 ,255});
	printf("ambient:%f\n", rt->scene.ambient_ligth.ratio);
}

t_err	rt_init(t_minirt *rt)
{
	t_err	err;

	err = rt_mlx_init(&rt->mlx);
	rt->scene.resolution_x = WIDTH;
	rt->scene.resolution_y = HEIGHT;
	rt->scene.viewport_x = WIDTH;
	rt->scene.viewport_y = HEIGHT;
	rt->scene.d = WIDTH;
	init_temp_scene(rt);

	return (err);
}
