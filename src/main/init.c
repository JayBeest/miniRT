/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:27:52 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/05/10 16:01:55 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

//void	clear_scene(t_scene *scene)
//{
//	t_rt_shape	*node;
//	t_rt_shape	*next;
//
//	node = scene->shapes;
//	while (node)
//	{
//		next = node->next;
//		free(node);
//		node = next;
//	}
//	node = scene->lights;
//	while (node)
//	{
//		next = node->next;
//		free(node);
//		node = next;
//	}
////	free (&scene->ambient_light);
//}

//t_err	init_temp_scene(t_minirt *rt)
//{
//#define GLOSSY_UN 150
//	rt->scene.origin = (t_vector){-50, 0, -1200};
//	rt->scene.shapes = new_sphere(250, (t_vector){-150, -50, 800}, (t_color){230, 0, 38, 255}, GLOSSY_UN);//RED
//	rt->scene.shapes->next = new_sphere(250, (t_vector){50, -10, 900}, (t_color){90, 187, 238, 255}, GLOSSY_UN);//BLUE
//	rt->scene.shapes->next->next = new_sphere(600, (t_vector){-450, -210, 1250}, (t_color){102, 255, 153, 255}, GLOSSY_UN);//GREEN
//	rt->scene.shapes->next->next->next = new_sphere(380, (t_vector){100, -360, 900}, (t_color){255, 255, 77, 255}, GLOSSY_UN);//YELLOW
//	rt->scene.shapes->next->next->next->next = new_sphere(4000, (t_vector){-280, -1200, 6000}, (t_color){241, 156, 187, 255}, 80);//PINK
//	rt->scene.shapes->next->next->next->next->next = new_plane((t_vector){-1, -630, 1000}, (t_vector){-0.1, -0.8, 0.1}, (t_color){255, 255, 255, 255}, 1000);
//
//	rt->scene.ambient_light = new_ambient_light(0.15, (t_color){255 , 196 , 215 , 255});
//	rt->scene.lights = new_point_light(0.8, (t_vector){-50, 10, 200}, (t_color){255 ,255 ,13 ,255});
//	rt->scene.lights->next = new_point_light(0.35, (t_vector){200, 50, 100}, (t_color){255 ,100 ,200 ,255});
//	rt->scene.lights->next->next = new_direct_light(0.55, (t_vector){2.5, 4.7, 3}, (t_color){190, 255 ,100 ,255});
//	rt->scene.lights->next->next->next = new_point_light(0.35, (t_vector){40, -150, -500}, (t_color){255 ,255 ,255 ,255});
//	rt->scene.lights->next->next->next->next = new_point_light(0.45, (t_vector){-150, -80, 200}, (t_color){255 ,255 ,255 ,255});
//	// printf("ambient:%f\n", rt->scene.ambient_light.ratio);
//	return (NO_ERR);
//}
//
//t_err	init_temp_scene2(t_minirt *rt)
//{
//#define GLOSSY_DEU 6000
//	rt->scene.origin = (t_vector){-50, 0, -1200};
//	rt->scene.shapes = new_sphere(250, (t_vector){-150, -50, 800}, (t_color){230, 0, 38, 255}, 2000);//RED
//	rt->scene.shapes->next = new_sphere(250, (t_vector){50, -10, 900}, (t_color){90, 187, 238, 255}, 2000);//BLUE
//	rt->scene.shapes->next->next = new_sphere(600, (t_vector){-450, -210, 1250}, (t_color){102, 255, 153, 255}, 6000);//GREEN
//	rt->scene.shapes->next->next->next = new_sphere(380, (t_vector){100, -360, 900}, (t_color){255, 255, 77, 255}, 3000);//YELLOW
//	rt->scene.shapes->next->next->next->next = new_sphere(4000, (t_vector){-280, -1200, 6000}, (t_color){241, 156, 187, 255}, 8000);//PINK
//	rt->scene.shapes->next->next->next->next->next = new_plane((t_vector){-1, -630, 1000}, (t_vector){-0.1, -0.8, 0.1}, (t_color){255, 255, 255, 255}, 1000);
//
//	rt->scene.ambient_light = new_ambient_light(0.15, (t_color){255 , 128 , 255 , 255});
//	rt->scene.lights = new_point_light(0.4, (t_vector){-50, 180, 200}, (t_color){255 ,21 ,255 ,255});
//	rt->scene.lights->next = new_point_light(0.35, (t_vector){200, 50, 100}, (t_color){255 ,200 ,56 ,255});
//	rt->scene.lights->next->next = new_direct_light(0.5, (t_vector){2.5, 4.7, 3}, (t_color){55, 255 ,255 ,255});
//	rt->scene.lights->next->next->next = new_point_light(0.35, (t_vector){40, -150, -500}, (t_color){255 ,255 ,255 ,255});
//	rt->scene.lights->next->next->next->next = new_point_light(0.60, (t_vector){-150, -80, 200}, (t_color){255 ,255 ,255 ,255});
//	// printf("ambient:%f\n", rt->scene.ambient_light.ratio);
//	return (NO_ERR);
//}
//
//t_err	init_temp_scene3(t_minirt *rt)
//{
//	rt->scene.origin = (t_vector){0, 0, 0};
//	rt->scene.shapes = new_sphere(1, (t_vector){0, -1, 3}, (t_color){230, 0, 38, 255}, 700);//RED
//	rt->scene.shapes->next = new_sphere(1, (t_vector){2, 0, 4}, (t_color){90, 187, 238, 255}, 100);//BLUE
//	rt->scene.shapes->next->next = new_sphere(1, (t_vector){-2, 0, 4}, (t_color){102, 255, 153, 255}, 500);//GREEN
//	// rt->scene.shapes->next->next->next = new_sphere(50, (t_vector){0, -5, 12}, (t_color){255, 255, 77, 255}, 50);//YELLOW
//	// rt->scene.shapes->next->next->next->next = new_sphere(4000, (t_vector){-250, -1200, 6000}, (t_color){241, 156, 187, 255}, 100);//PINK
//	// rt->scene.shapes->next->next->next->next->next = new_plane((t_vector){-100, 0, 0}, (t_vector){0, 1, 0}, (t_color){255, 255, 0, 255}, 100);
//
//	rt->scene.ambient_light = new_ambient_light(0.4, (t_color){255 , 255 , 255 , 255});
//	// rt->scene.lights = new_point_light(0.2, (t_vector){200, 100, 0}, (t_color){255 ,255 ,255 ,255});
////	rt->scene.lights->next = new_point_light(0.2, (t_vector){500, 0, -1500}, (t_color){255 ,255 ,255 ,255});
//	// rt->scene.lights->next = new_direct_light(0.2, (t_vector){1, 4, 4}, (t_color){255 ,255 ,255 ,255});
////	rt->scene.lights->next->next->next = new_point_light(0.3, (t_vector){400, -10, 300}, (t_color){255 ,255 ,255 ,255});
//	// printf("ambient:%f\n", rt->scene.ambient_light.ratio);
//	return (NO_ERR);
//}

t_err	rt_init(t_minirt *rt)
{
	t_err	err;

	err = rt_mlx_init(&rt->mlx);
	rt->scene.resolution_x = WIDTH;
	rt->scene.resolution_y = HEIGHT;
	rt->scene.viewport_x = 1;
	rt->scene.viewport_y = 1;
	rt->scene.d = 1;
	rt->scene.cameras.type = CAMERA;
	rt->scene.lights.type = LIGHT_P;
//	rt->scene.planes.type = PLANE;
//	rt->scene.spheres.type = SPHERE;
//	rt->scene.cylinders.type = CYLINDER;
	return (err);
}
