/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:49 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:50 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

t_vector	canvas_to_viewport(int x, int y, t_scene scene);
t_color		multip_color(t_color_intensity intensity, t_color color);

#endif