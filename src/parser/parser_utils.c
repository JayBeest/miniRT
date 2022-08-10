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

t_err	get_resolution(char *line, int *resolution)
{
	int	i;

	i = 0;
	printf("	[get_resolution]\n");
	if (!ft_isdigit(*line) || ft_strlen(line) > 4)
	{
		printf(YEL "[get_resolution] not a radius?\n" RESET);
		return (PARSE_F);
	}
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
		{
			printf(YEL "[get_resolution] non digit?\n" RESET);
			return (PARSE_F);
		}
		i++;
	}
	*resolution = ft_atoi(line);
	if (*resolution > 0 && *resolution <= 2160)
		return (NO_ERR);
	printf(YEL "[get_resolution] radius not in range\n" RESET);
	return (PARSE_F);
}

t_err	get_radius(char *line, double *radius)
{
	int	i;

	i = 0;
	printf("	[get_radius]\n");
	if (!ft_isdigit(*line) || ft_strlen(line) > 5)
	{
		printf(YEL "[get_radius] not a radius?\n" RESET);
		return (PARSE_F);
	}
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
		{
			printf(YEL "[get_radius] non digit?\n" RESET);
			return (PARSE_F);
		}
		i++;
	}
	*radius = ft_atof(line) / 2;
	if (*radius > 0 && *radius < 20000)
		return (NO_ERR);
	printf(YEL "[get_radius] radius not in range\n" RESET);
	return (PARSE_F);
}

t_err	get_fov(char *line, int *fov)
{
	int	i;

	i = 0;
	printf("	[get_fov]\n");
	if (!ft_isdigit(*line) || ft_strlen(line) > 3)
	{
		printf(YEL "[get_fov] not a fov\n" RESET);
		return (PARSE_F);
	}
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
		{
			printf(YEL "[get_fov] non digit?\n" RESET);
			return (PARSE_F);
		}
		i++;
	}
	*fov = ft_atoi(line);
	if (*fov <= 180 && *fov >= 0)
		return (NO_ERR);
	printf(YEL "[get_fov] fov not in range\n" RESET);
	return (PARSE_F);
}

t_err	get_ratio(char *line, double *ratio)
{
	printf("	[parse ratio]\n");
	if (!ft_strisfloat(line))
	{
		printf(YEL "[get_ratio] not a float\n" RESET);
		return (PARSE_F);
	}
	*ratio = ft_atof(line);
	if (*ratio > 0 || *ratio < 1)
		return (NO_ERR);
	printf(YEL "[get_ratio] ratio not in range\n" RESET);
	return (PARSE_F);
}

t_err	get_pos(char *str, double *pos)
{
	int i;
	int count;

	i = 0;
	count = ft_strlen(str);
	if (count > 6 || count < 1)//meer??
	{
		printf("[get_pos] pos too large?\n");
		return (-1);
	}
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (i < count && (ft_isdigit(str[i]) || str[i] == '.'))
		i++;
	if (i != count)
	{
		printf("[get_pos] nondigit?\n");
		return (PARSE_F);
	}
	*pos = ft_atof(str);
	return (NO_ERR);
}

t_err	get_xyz(char *line, t_vector *pos)
{
	char	**split;

	printf("	[get_xyz]\n");
	split = ft_split(line, ',');
	if (!split)
		return (MALLOC_F);
	if (ft_count_split(split) != 3)
	{
		printf("[get_xyz] argc err\n");
		return (PARSE_F);
	}
	if (get_pos(split[0], &pos->x) != NO_ERR)
		return (PARSE_F);
	if (get_pos(split[1], &pos->y) != NO_ERR)
		return (PARSE_F);
	if (get_pos(split[2], &pos->z) != NO_ERR)
		return (PARSE_F);
	return (NO_ERR);
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

t_err	parse_rgb(char *line, t_color *color)
{
	char	**split;

	printf("	[parse_rgb]\n");
	split = ft_split(line, ',');
	if (!split)
		return (MALLOC_F);
	if (ft_count_split(split) != 3)
	{
		printf("[parse_rgb] argc err\n");
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