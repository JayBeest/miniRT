/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:38 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 14:13:29 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <datatypes.h>

#include <stdio.h>

t_rt_shape *new_rt_object(t_rt_shape_type type)
{
	t_rt_shape *obj;
	
	obj = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (obj)
		obj->type = type;
	return (obj);
}

char	*skip_float(char *line)
{
	if (*line == '-' || *line == '+')
		line++;
	while (ft_isdigit(*line))
		line++;
	if (*line == '.')
		line++;
	while (ft_isdigit(*line))
		line++;
	return (line);
}

t_err	parse_ratio(char *line, double *ratio)
{
//	printf("parsing ratio: %s\n", line);
	if (!ft_strisfloat(line))
	{
		printf(YEL "[parse_ratio] not a float\n" RESET);
		return (PARSE_F);
	}
	*ratio = ft_atof(line);
	if (*ratio > 0 || *ratio < 1)
		return (NO_ERR);
	printf(YEL "[parse_ratio] ratio not in range\n" RESET);
	return (PARSE_F);
}

t_err	parse_color(char *line, t_color *color)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
//	if (i > 4)
//		return (PARSE_F);
	color->r = ft_atoi(line);
	if (line[i] != ',')
		return (PARSE_F);
	line = line + i + 1;
	i = 0;
	while (ft_isdigit(line[i]))
		i++;
//	if (i > 4)
//		return (PARSE_F);
	color->g = ft_atoi(line);
	if (line[i] != ',')
		return (PARSE_F);
	line = line + i + 1;
	i = 0;
	while (ft_isdigit(line[i]))
		i++;
//	if (i > 4)
//		return (PARSE_F);
	color->b = ft_atoi(line);
	color->a = 255;
	return (NO_ERR);
}