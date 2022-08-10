/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:47 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 20:23:16 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
#define LIGHTING_H

t_color	precalculate_light(int closest_shape, t_vector o, t_vector d, double closest_t, t_scene scene);

#endif
