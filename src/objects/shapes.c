/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:26 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 14:14:01 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <datatypes.h>

t_rt_shape *new_sphere(int radius, t_vector pos, t_color color, int specular)
{
	t_rt_shape	*obj;
	static int	id;

	obj = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (!obj)
		return (obj);
	obj->id = id++;
	obj->type = SPHERE;
	obj->radius = radius;
	obj->vector = pos;
	obj->color = color;
	obj->specular = specular;
	return (obj);
}

t_rt_shape *new_plane(t_vector pos, t_vector vector, t_color color, int specular)
{
	t_rt_shape	*obj;

	obj = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (!obj)
		return (obj);
	obj->type = PLANE;
	obj->pos1 = pos;
	obj->vector = vector;
	obj->color = color;
	obj->specular = specular;
	return (obj);
}
