/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:52 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 15:44:57 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

t_intersect_result	get_closest_intersection(t_rt_obj_shape *node, t_vector o, t_vector d, double t_min, double t_max, int self_id);
t_err	            render_scene(t_minirt *rt);

#endif