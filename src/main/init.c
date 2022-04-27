/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:27:52 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 16:43:11 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <datatypes.h>
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

t_err	init_temp_scene(t_minirt *rt)
{
	rt->scene.origin = (t_vector){150, 0, -1200};
	rt->scene.shapes = new_sphere(250, (t_vector){-150, -80, 800}, (t_color){230, 0, 38, 255}, 100);//RED
	rt->scene.shapes->next = new_sphere(250, (t_vector){50, 20, 900}, (t_color){90, 187, 238, 255}, 100);//BLUE
	rt->scene.shapes->next->next = new_sphere(600, (t_vector){-450, -180, 1250}, (t_color){102, 255, 153, 255}, 100);//GREEN
	rt->scene.shapes->next->next->next = new_sphere(380, (t_vector){100, -330, 900}, (t_color){255, 255, 77, 255}, 100);//YELLOW
	rt->scene.shapes->next->next->next->next = new_sphere(4000, (t_vector){-250, -1200, 6000}, (t_color){241, 156, 187, 255}, 100);//PINK
//	rt->scene.shapes->next->next->next->next->next = new_plane((t_vector){-500, 0, 12500}, (t_vector){0, 0, 0.8}, (t_color){255, 255, 0, 255});

	rt->scene.ambient_ligth = new_ambient_light(0.1, (t_color){255 ,255 ,255 ,255});
	rt->scene.lights = new_point_light(0.3, (t_vector){-50, 180, 100}, (t_color){255 ,255 ,255 ,255});
	rt->scene.lights->next = new_point_light(0.3, (t_vector){100, 0, 100}, (t_color){255 ,255 ,255 ,255});
	rt->scene.lights->next->next = new_point_light(0.3, (t_vector){400, -10, 300}, (t_color){255 ,255 ,255 ,255});
	// printf("ambient:%f\n", rt->scene.ambient_ligth.ratio);
	return (NO_ERR);
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
	return (err);
}
