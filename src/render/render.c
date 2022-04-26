/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:30:02 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:30:03 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <datatypes.h>
#include <render_utils.h>
#include <draw_utils.h>
#include <intersect.h>
#include <lighting.h>
#include <math.h>

#include <pthread.h>
#include <stdio.h>

t_color	trace_ray(t_vector o, t_vector d, t_scene scene)
{
	t_rt_shape		*node;
	double			closest_t;
	t_rt_shape		*closest_sphere;
	t_quad_result	quad_result;

	int				edge;
//	int				d_edge;

	closest_sphere = NULL;
	node = scene.shapes;
	closest_t = INFINITY;
	while (node)
	{
		edge = 0;
//		d_edge = 0;
		quad_result = intersect_shape(o, d, node);
		if (quad_result.t1 < 1000 && quad_result.t1 > 1 && quad_result.t1 == quad_result.t2)
		{
			printf(RED "edge found!!\n" RESET);
			closest_t = quad_result.t1;
			closest_sphere = node;
			edge = 1;
		}
		else
		{
			if (quad_result.t1 > 1 && quad_result.t1 < 1000 && quad_result.t1 < closest_t)
			{
				closest_t = quad_result.t1;
				closest_sphere = node;
				edge = 0;
			}
			if (quad_result.t2 > 1 && quad_result.t2 < 1000 && quad_result.t2 < closest_t)
			{
				closest_t = quad_result.t2;
				closest_sphere = node;
				edge = 0;
			}
		}
		node = node->next;
	}
	if (!closest_sphere)
		return ((t_color){0, 0, 0, 255});
	if (edge)
		return ((t_color){0, 255, 204, 255});
	return (precalculate_light(closest_sphere, o, d, closest_t, scene));
}

t_mult_pixel	get_multi_pix(t_scene scene, int id)
{
	t_mult_pixel	multi_pix;

	if (id  == 0)
	{
		multi_pix.min_x = -1 * scene.resolution_x / 2;
		multi_pix.max_x = 0;
		multi_pix.min_y = 0;
		multi_pix.max_y = scene.resolution_y / 2;
	}
	else if (id == 1)
	{
		multi_pix.min_x = 0;
		multi_pix.max_x = scene.resolution_x /2;
		multi_pix.min_y = 0;
		multi_pix.max_y = scene.resolution_y / 2;
	}
	else if (id == 2)
	{
		multi_pix.min_x = -1 * scene.resolution_x / 2;
		multi_pix.max_x = 0;
		multi_pix.min_y = -1 * scene.resolution_y / 2;
		multi_pix.max_y = 0;
	}
	else
	{
		multi_pix.min_x = 0;
		multi_pix.max_x = scene.resolution_x / 2;
		multi_pix.min_y = -1 * scene.resolution_y / 2;
		multi_pix.max_y = 0;
	}
	return (multi_pix);
}

void	*render_thread(void *arg)
{
	t_minirt		*rt;
	t_mult_pixel	m_pix;
	int 			x;
	int 			y;
	t_vector		d;
	t_color			color;

//	printf("this is pthread :%d\n", ((t_pthr_arg *)arg)->id);
	rt = ((t_pthr_arg *)arg)->rt;
	m_pix = get_multi_pix(rt->scene, ((t_pthr_arg *)arg)->id);
	x = m_pix.min_x;
	while (x < m_pix.max_x)
	{
		y = m_pix.min_y;
		while (y < m_pix.max_y)
		{
			d = canvas_to_viewport(x, y, rt->scene);
			color = trace_ray(rt->scene.origin, d, rt->scene);
			rt_putpixel(x, y, color_to_int(color), rt);
			y++;
		}
		x++;
	}
	return (NULL);
}

t_err	render_scene(t_minirt *rt)
{
	pthread_t	pthread[4];
	t_pthr_arg	arg[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		arg[i].id = i;
		arg[i].rt = rt;
		i++;
	}
	i = 0;
//	pthread_create(&pthread[i], NULL, &render_thread, &arg[i]);
	while (i < 4)
	{
		if (pthread_create(&pthread[i], NULL, &render_thread, &arg[i]))
			printf("pthread id[%d] failed\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}
	return (NO_ERR);
}
