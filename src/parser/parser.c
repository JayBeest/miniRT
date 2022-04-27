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

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <datatypes.h>
#include <parser_utils.h>

#include <stdio.h>


t_err	parse_ambient(char *line, t_rt_shape *ambient_light)
{
	printf("[parse_ambient]\n");
	line = ft_skipspace(line);
	if (parse_ratio(line, &ambient_light->ratio) != NO_ERR)
		return (PARSE_F);
	line = skip_float(line);
	line = ft_skipspace(line);
	if (parse_color(line, &ambient_light->color) != NO_ERR)
	{
		printf("[parse_ambient] colour fail %s\n", line);
		return (PARSE_F);
	}
	return (NO_ERR);
}

t_err	parse_xyz(char *line, t_vector *pos)
{
	printf("[parse_xyz] start line: %s\n", line);
	if (!ft_strisfloat(line))
	{
		printf(YEL "[parse_xyz] not a float\n" RESET);
		return (PARSE_F);
	}
	pos->x = ft_atof(line);
	line = skip_float(line);
	printf(YEL "xyz: line: %s\n" RESET, line);
	return (NO_ERR);
}

t_err	parse_camera(char *line, t_scene *scene)
{
	t_rt_shape	*new;

	printf("[parse_camera]\n");
	new = new_rt_object(NO_OBJECT);
	if (!new)
		return (MALLOC_F);
	line = ft_skipspace(line);
	if (parse_xyz(line, &new->pos1) != NO_ERR)
	{
		free(new);
		return (PARSE_F);
	}
	scene->cameras = new;
	return (NO_ERR);
}

t_err	parse_light(char *line, t_scene *scene)
{
	(void)scene;
	(void)line;
	printf("[parse_light]\n");
	return (NO_ERR);
}

t_err	parse_sphere(char *line, t_scene *scene)
{
	(void)scene;
	(void)line;
	printf("[parse_sphere]\n");
	return (NO_ERR);
}

t_err	parse_plane(char *line, t_scene *scene)
{
	(void)scene;
	(void)line;
	printf("[parse_plane]\n");
	return (NO_ERR);
}

t_err	parse_cylinder(char *line, t_scene *scene)
{
	(void)scene;
	(void)line;
	printf("[parse_cylinder]\n");
	return (NO_ERR);
}


t_err	parse_line(char *line, t_scene *scene)
{
	if (*line)
	{
		printf("parsing line: %s$\n", line);
		line = ft_skipspace(line);
		if (ft_strncmp(line, "A ", 2) == 0)
			return (parse_ambient(line + 2, &scene->ambient_ligth));
		else if (ft_strncmp(line, "C ", 2) == 0)
			return (parse_camera(line + 2, scene));
		else if (ft_strncmp(line, "L ", 2) == 0)
			return (parse_light(line + 2, scene));
		else if (ft_strncmp(line, "sp ", 3) == 0)
			return (parse_sphere(line + 3, scene));
		else if (ft_strncmp(line, "pl ", 3) == 0)
			return (parse_plane(line + 3, scene));
		else if (ft_strncmp(line, "cy ", 3) == 0)
			return (parse_cylinder(line + 3, scene));
		else
			return (INVALID_OBJ);
	}
	return (NO_ERR);
}

t_err	parse_file(const char *arg)
{
	(void)arg;
	///if correct extension

	return (NO_ERR);
}

t_err	parse_input(const char *arg, t_scene *scene)
{
	t_err	err;
	int 	fd;
	char	*line;

	err = parse_file(arg);
	if (err != NO_ERR)
		return (err);
	fd = open(arg, O_RDONLY, 0644);
	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		if (parse_line(line, scene) != NO_ERR)
			return (printf(RED "invalid object in line: %s\n" RESET, line));
		free(line);
	}
	close(fd);
	/// check min req
	return (NO_ERR);
}