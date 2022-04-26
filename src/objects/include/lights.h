/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lights.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:13 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:14 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
#define LIGHTS_H

t_rt_shape	new_ambient_light(double ratio, t_color color);
t_rt_shape	*new_point_light(double ratio, t_vector pos, t_color color);

#endif
