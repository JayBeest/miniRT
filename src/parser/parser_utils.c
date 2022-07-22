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

t_rt_shape *new_rt_object(t_rt_obj_type type)
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

int	get_color(char *str)
{
	int i;
	int count;
	int color;

	i = 0;
	count = ft_strlen(str);
	if (count > 3 || count < 1)
	{
		printf("[get_color] too many args\n");
		return (-1);
	}
	while (i < count)
	{
		if (!ft_isdigit(str[i]))
		{
			printf("[get_color] non digit?\n");
			return (-1);
		}
		i++;
	}
	color = ft_atoi(str);
	if (color > 255 || color < 0)
	{
		printf("[get_color] rgb out of range (0-255)\n");
		return (-1);
	}
	return (color);
}

t_err	parse_color(char *line, t_color *color)
{
	char	**split;

	split = ft_split(line, ',');
	if (!split)
		return (MALLOC_F);
	if (ft_count_split(split) != 3)
	{
		printf("[parse_color] argc err\n");
		return (PARSE_F);
	}
	color->r = get_color(split[0]);
	color->g = get_color(split[1]);
	color->b = get_color(split[2]);
	color->a = 255;
	if (color->r > 255 || color->g > 255 || color->b > 255)
		return (PARSE_F);
	return (NO_ERR);
}