/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/05/10 16:43:11 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft.h>
#include <datatypes.h>
#include <render.h>
#include <render_utils.h>
#include <vector_utils.h>
#include <draw_utils.h>

#include <stdio.h>

void	init_intensity(t_color_intensity *intensity, double intens_to_add, t_color color)
{
	intensity->r = (color.r / 255) * intens_to_add;
	intensity->g = (color.g / 255) * intens_to_add;
	intensity->b = (color.b / 255) * intens_to_add;
	intensity->a = (color.a / 255) * intens_to_add;
}

void	update_intensity(t_color_intensity *intensity, t_color_intensity intens_to_add, t_color color)
{
	intensity->r += (color.r / 255) * intens_to_add.r;
	intensity->g += (color.g / 255) * intens_to_add.g;
	intensity->b += (color.b / 255) * intens_to_add.b;
	intensity->a += (color.a / 255) * intens_to_add.a;
}

t_color_intensity	update_multiply_intensity(t_color_intensity ori_intens, double intens_to_multip, t_color color)
{
	ori_intens.r *= (color.r / 255) * intens_to_multip;
	ori_intens.g *= (color.g / 255) * intens_to_multip;
	ori_intens.b *= (color.b / 255) * intens_to_multip;
	ori_intens.a *= (color.a / 255) * intens_to_multip;
	return (ori_intens);
}

t_color	calculate_light(int shape, t_vector n, t_vector p, t_vector v, t_scene scene)
{
	t_color_intensity	intensity;
//	t_color_intensity 	intens_to_add;
//	t_vector			r;
//	t_vector			l;
//	double				n_dot_l;
//	double				r_dot_v;
	t_intersect_result	shadow;
//	int 				i;
//
//	i = 0;
	// (void)r_dot_v;
	 (void)n;
	 (void)p;
	 (void)v;
	// (void)r;
	ft_bzero(&shadow, sizeof(t_intersect_result));
	init_intensity(&intensity, scene.ambient_light.ratio, scene.ambient_light.color);
//	while (i < scene.lights.amount)
//	{
//		t_vector lp = substract_vector(((t_rt_obj_light *)(scene.lights.obj))[i].position, p);
//		t_vector ln = substract_vector(((t_rt_obj_light *)(scene.lights.obj))[i].position, n);
//		if (((t_rt_obj_light *)(scene.lights.obj))[i].type == LIGHT_P)
//		{
//			l = lp;
//			shadow = get_closest_intersection(scene.shapes, p, l, EPSILON, 1, shape);
//		}
//		else if (scene.lights->type == LIGHT_D)
//		{
//			l = scene.lights->vector;
//			shadow = get_closest_intersection(scene.shapes, p, l, EPSILON, INFINITY, shape);
//		}
//		 if (shadow.closest_shape && shadow.closest_shape != shape)
//		 {
//		 	scene.lights = scene.lights->next;
//		 	continue ;
//		 }
//		if (scene.lights->type == LIGHT_P)
//			l = ln;
//		n_dot_l = dot_product(n, l);
//		if (n_dot_l > 0)
//		{
//			init_intensity(&intens_to_add, scene.lights->ratio * n_dot_l / (sqrt(dot_product(n, n)) * sqrt(dot_product(l, l))), scene.lights->color);
//			update_intensity(&intensity, intens_to_add, scene.lights->color);
//		}
//		(void)lp;
//		(void)ln;
//		(void)v;
//		(void)r;
//		(void)r_dot_v;
//		if (scene.lights->specular != -1)
//		{
//			// printf("shape_id: %d specular: %d\n", shape->id, shape->specular);
//			if (scene.lights->type == LIGHT_D)
//				l = lp;
//
//			r = multip_vector(n, 2);
//			r = multip_vector(r, dot_product(n, l));
//			r = substract_vector(r, l);
//			r_dot_v = dot_product(r, v);
////			(void)r_dot_v;
//			if (r_dot_v > 0)
//			{
//				intens_to_add = update_multiply_intensity(intensity, pow(r_dot_v / (sqrt(dot_product(r, r)) * sqrt(dot_product(v, v))), shape->specular), scene.lights->color);
//				update_intensity(&intensity, intens_to_add, scene.lights->color);
//			}
//		}
//		scene.lights = scene.lights->next;
//	}
	return (multip_color(intensity, ((t_rt_obj_shape *)(scene.shapes.obj))[shape].color));
}

t_color	precalculate_light(int closest_shape, t_vector o, t_vector d, double closest_t, t_scene scene)
{
	t_vector	p;
	t_vector	n;
	t_vector	v;

	p = multip_vector(d, closest_t);
	p = add_vector(p, o);
	n = substract_vector(p, ((t_rt_obj_shape *)(scene.shapes.obj))[closest_shape].position);
	n = multip_vector(n, (double)1 / sqrt(dot_product(n, n)));
	if (((t_rt_obj_shape *)(scene.shapes.obj))[closest_shape].specular != -1)
		v = multip_vector(d, -1);
	else
		v = (t_vector){0, 0, 0};
	return (calculate_light(closest_shape, n, p, v, scene));
}
