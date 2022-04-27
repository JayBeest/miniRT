/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 18:58:31 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <datatypes.h>
#include <render.h>
#include <render_utils.h>
#include <vector_utils.h>
#include <draw_utils.h>

#include <stdio.h>

t_color	calculate_light(t_rt_shape *shape, t_vector n, t_vector p, t_vector v, t_scene scene)
{
	double				intensity;
	t_vector			r;
	t_vector			l;
	double				n_dot_l;
	double				r_dot_v;
	t_intersect_result	shadow;

	intensity = scene.ambient_ligth.ratio;
	while (scene.lights)
	{
		l = substract_vector(scene.lights->pos1, p);
		shadow = get_closest_intersection(shape, p, l, 0.001, T_MAX);
		if (shadow.closest_shape)
		{
			scene.lights = scene.lights->next;
			continue ;
		}
		n_dot_l = dot_product(n, l);
		if (n_dot_l >= 0)
			intensity += scene.lights->ratio * n_dot_l / (sqrt(dot_product(n, n)) * sqrt(dot_product(l, l)));
		if (scene.lights->specular != -1)
		{
			// printf("shape_id: %d specular: %d\n", shape->id, shape->specular);
			r = multip_vector(n, 2);
			r = multip_vector(r, dot_product(n, l));
			r = substract_vector(r, l);
			r_dot_v = dot_product(r, v);
			if (r_dot_v)
				intensity += intensity * pow(r_dot_v / (sqrt(dot_product(r, r)) * sqrt(dot_product(v, v))), shape->specular);
		}
		scene.lights = scene.lights->next;
	}
	return (multip_color(intensity, shape->color));
}

t_color	precalculate_light(t_rt_shape *shape, t_vector o, t_vector d, double closest_t, t_scene scene)
{
	t_vector	p;
	t_vector	n;
	t_vector	v;

	p = multip_vector(d, closest_t);
	p = add_vector(p, o);
	n = substract_vector(p, shape->pos1);
	n = multip_vector(n, (double)1 / sqrt(dot_product(n, n)));
	if (shape->specular != -1)
		v = multip_vector(d, -1);
	else
		v = (t_vector){0, 0, 0};
	return (calculate_light(shape, p, n, v, scene));
}
