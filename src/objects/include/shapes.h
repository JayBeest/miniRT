/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:17 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:18 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

t_rt_shape *new_sphere(int radius, t_vector pos, t_color color, int specular);
t_rt_shape *new_plane(t_vector pos, t_vector vector, t_color color, int specular);

#endif