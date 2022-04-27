/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:00 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 21:00:25 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <datatypes.h>
#include <init.h>
#include <parser.h>
#include <render.h>
#include <stdio.h>
#include <stdlib.h>

int g_scene_switch;
int g_animate;

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

	if (!g_animate)
		goto skip_animation;
	static int toggle = 1;
	if (toggle)
	{
		if (rt->scene.lights->pos1.x == 250)
			toggle = 0;
		else
		{
			rt->scene.lights->pos1.x+=5;
			rt->scene.lights->pos1.z+=5;
		}
	}
	else
	{
		if (rt->scene.lights->pos1.x == -350)
			toggle = 1;
		else
		{
			rt->scene.lights->pos1.x-=5;	
			rt->scene.lights->pos1.z-=5;
		}
	}
	static int toggle2 = 1;
	if (toggle2)
	{
		if (rt->scene.lights->next->pos1.y == 800)
			toggle2 = 0;
		else
		{
			rt->scene.lights->next->pos1.y+=10;
		}
	}
	else
	{
		if (rt->scene.lights->next->pos1.y == -400)
			toggle2 = 1;
		else
		{
			rt->scene.lights->next->pos1.y-=10;
		}
	}
	goto skip_animation;
	skip_animation:
	render_scene(rt);
}

int	main(int argc, char *argv[])
{
	t_minirt	rt;
	t_err		err;

	g_animate = 0;
	ft_bzero(&rt, sizeof(rt));
	err = rt_init(&rt);
	if (err != NO_ERR)
		return (err);
	g_scene_switch = 0;
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "-a", 3) == 0)
			g_animate = 1;
		else
			g_scene_switch = 1;
		if (g_scene_switch || (g_animate == 1 && argc > 2))
			err = init_temp_scene2(&rt);
		else
			err = init_temp_scene(&rt);
//		err = parse_input(argv[1], &rt.scene);
//		return (EXIT_SUCCESS);
	}
	else
		err = init_temp_scene(&rt);
	if (err != NO_ERR)
		return (err);
	ft_memset(rt.mlx.img->pixels, 255, rt.mlx.img->width * rt.mlx.img->height * sizeof(int));

//	printf("rgba 128/128/128/0: %X\n", color_to_int((t_color){97, 97, 97, 255}));
	// rt_putpixel(0, 0, color_to_int((t_color){255, 255, 255, 255}), &rt);
	// render_scene(&rt);
	mlx_image_to_window(rt.mlx.mlx, rt.mlx.img, 0, 0);
	mlx_loop_hook(rt.mlx.mlx, &hook, &rt);
	mlx_loop(rt.mlx.mlx);
	mlx_terminate(rt.mlx.mlx);
	return (EXIT_SUCCESS);
}