#include <libft.h>
#include <datatypes.h>
#include <main.h>
#include <init.h>
#include <draw.h>

#include <stdio.h>
#include <stdlib.h>

void	hook(void *arg)
{
	t_minirt	*rt;
	t_mlx		*mlx;

	rt = arg;
	mlx = &rt->mlx;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
		mlx->img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
		mlx->img->instances[0].y += 5;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
		mlx->img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
		mlx->img->instances[0].x += 5;

	static int toggle = 1;
	if (toggle)
	{
		if (rt->scene.d == 20)
			toggle = 0;
		else
			rt->scene.d++;
	}
	else
	{
		if (rt->scene.d == 1)
			toggle = 1;
		else
			rt->scene.d--;
	}
	render_scene(rt);
}

int	main(void)
{
	t_minirt	rt;
	t_err		err;

	ft_bzero(&rt, sizeof(rt));
	err = rt_init(&rt);
	if (err != NO_ERR)
		return (err);

	ft_memset(rt.mlx.img->pixels, 255, rt.mlx.img->width * rt.mlx.img->height * sizeof(int));

//	printf("rgba 128/128/128/0: %X\n", color_to_int((t_color){97, 97, 97, 255}));
	rt_putpixel(0, 0, color_to_int((t_color){255, 255, 255, 255}), &rt);

	mlx_image_to_window(rt.mlx.mlx, rt.mlx.img, 0, 0);
	mlx_loop_hook(rt.mlx.mlx, &hook, &rt);
	mlx_loop(rt.mlx.mlx);
	mlx_terminate(rt.mlx.mlx);
	return (EXIT_SUCCESS);
}