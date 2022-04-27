/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:56 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <datatypes.h>
#include <render_utils.h>
#include <vector_utils.h>
#include <draw_utils.h>

t_color	calculate_light(t_rt_shape *shape, t_vector n, t_vector p, t_vector s, t_scene scene)
{
	double		intensity;
//	int			i;
	t_vector	l;
	double		n_dot_l;

//	i = 0;
	(void)s;
	intensity = scene.ambient_ligth.ratio;
	while (scene.lights)
	{
		l = substract_vector(scene.lights->pos1, p);
		n_dot_l = dot_product(n, l);
		if (n_dot_l > 0)
			intensity += scene.lights->ratio * n_dot_l / (sqrt(dot_product(n, n)) * sqrt(dot_product(l, l)));
		if (scene.lights->specular != -1)
		{

		}
		scene.lights = scene.lights->next;
	}
	return (multip_color(intensity, shape->color));
}

t_color	precalculate_light(t_rt_shape *shape, t_vector o, t_vector d, double closest_t, t_scene scene)
{
	t_vector	p;
	t_vector	n;
	t_vector	s;

	p = multip_vector(d, closest_t);
	p = add_vector(p, o);
	n = substract_vector(p, shape->pos1);
	n = multip_vector(n, (double)1 / sqrt(dot_product(n, n)));
	s = multip_vector(d, -1);
	return (calculate_light(shape, p, n, s, scene));
}
