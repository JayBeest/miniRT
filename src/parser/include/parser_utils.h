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

t_rt_shape	*new_rt_object(t_rt_shape_type type);
char		*skip_float(char *line);
t_err		parse_ratio(char *line, double *ratio);
t_err		parse_color(char *line, t_color *color);

#endif