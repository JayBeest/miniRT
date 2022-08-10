/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lights.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:22 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:23 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <datatypes.h>
#include <libft.h>

t_rt_shape	new_ambient_light(double ratio, t_color color)
{
	t_rt_shape light;

	light.ratio = ratio;
	light.color = color;
	return (light);
}

t_rt_shape	*new_point_light(double ratio, t_vector pos, t_color color)
{
	t_rt_shape *light;

	light = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (!light)
		return (light);
	light->type = LIGHT_P;
	light->ratio = ratio;
	light->color = color;
	light->pos1 = pos;
	return (light);
}

t_rt_shape	*new_direct_light(double ratio, t_vector vector, t_color color)
{
	t_rt_shape *light;

	light = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (!light)
		return (light);
	light->type = LIGHT_D;
	light->ratio = ratio;
	light->color = color;
	light->vector = vector;
	return (light);
}