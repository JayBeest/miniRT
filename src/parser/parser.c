/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:40 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:29:43 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <datatypes.h>

t_err	parse_file(const char *arg)
{
	(void)arg;

	return (NO_ERR);
}

t_err	parse_input(const char *arg, t_scene *scene)
{
	t_err	err;

	err = parse_file(arg);
	if (err != NO_ERR)
		return (err);
	(void)scene;
	return (NO_ERR);
}