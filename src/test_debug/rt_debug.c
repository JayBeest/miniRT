/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_debug.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:30:09 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 17:48:48 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <datatypes.h>
#include <stdio.h>

void    print_vector(t_vector vec)
{
    printf("vector -- x:%f y:%f z:%f\n", vec.x, vec.y, vec.z);
}