/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:38 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:39 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <datatypes.h>

t_rt_shape *new_rt_object(t_rt_shape_type type)
{
	t_rt_shape *obj;

	obj = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (obj)
		obj->type = type;
	return (obj);
}