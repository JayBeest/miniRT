/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:10 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/05/02 13:42:45 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

t_err	rt_init(t_minirt *rt);
void	clear_scene(t_scene *scene);
t_err	init_temp_scene(t_minirt *rt);
t_err	init_temp_scene2(t_minirt *rt);

#endif