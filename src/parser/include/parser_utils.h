/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:33 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:34 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

t_rt_obj_shape	*new_rt_object(t_rt_obj_type type);
char		*skip_float(char *line);
t_err		get_ratio(char *line, double *ratio);
t_err		parse_rgb(char *line, t_color *color);
t_err		get_pos(char *str, double *pos);
t_err		get_xyz(char *line, t_vector *pos);
t_err		get_fov(char *line, int *fov);
t_err		get_radius(char *line, double *radius);
t_err		get_resolution(char *line, int *resolution);

#endif