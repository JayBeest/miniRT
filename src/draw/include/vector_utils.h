/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:51 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:28:52 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_H
# define VECTOR_UTILS_H

t_vector	add_vector(t_vector a, t_vector b);
t_vector	substract_vector(t_vector a, t_vector b);
t_vector	multip_vector(t_vector a, double num);
t_vector	cross_product(t_vector a, t_vector b);
double		dot_product(t_vector a, t_vector b);

#endif