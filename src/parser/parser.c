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

int	count_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

t_err	parse_ambient(char **split, t_rt_obj_ambient *ambient)
{
	printf("[parse_ambient]\n");
	if (count_split(split) != 3)
	{
		printf("Ambient incorrect argc\n");
		return (PARSE_F);
	}
	if (parse_ratio(split[1], &ambient->ratio) != NO_ERR)
		return (PARSE_F);
	if (parse_color(split[2], &ambient->color) != NO_ERR)
	{
		printf("[parse_ambient] colour fail %s\n", split[2]);
		return (PARSE_F);
	}
	return (NO_ERR);
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
	while (i < count && ft_isdigit(str[i]))
		i++;
	if (i != count)
	{
		printf("[get_pos] nondigit?\n");
		return (PARSE_F);
	}
	*pos = ft_atof(str);
	return (NO_ERR);
}

t_err	parse_xyz(char *line, t_vector *pos)
{
	char	**split;

	printf("[parse_xyz]\n");
	if (!ft_isdigit(line[0]))
		return (PARSE_F);
	split = ft_split(line, ',');
	if (!split)
		return (MALLOC_F);
	if (ft_count_split(split) != 3)
	{
		printf("[parse_xyz] argc err\n");
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

t_err	parse_camera(char **split, t_rt_object *object)
{
	t_err		err;
	static int	id;

	err = parse_xyz(split[1], &(((t_rt_obj_camera *)(object->obj))[id]).position);
	id++;
	return (err);
}

t_err	parse_light(char **split, t_scene *scene)
{
	(void)scene;
	(void)split;
	printf("[parse_light]\n");
	return (NO_ERR);
}

t_err	parse_resolution(char **split, t_scene *scene)
{
	(void)scene;
	(void)split;
	printf("[parse_resolution]\n");
	return (NO_ERR);
}

t_err	parse_sphere(char **split, t_scene *scene)
{
	(void)scene;
	(void)split;
	printf("[parse_sphere]\n");
	return (NO_ERR);
}

t_err	parse_plane(char **split, t_scene *scene)
{
	(void)scene;
	(void)split;
	printf("[parse_plane]\n");
	return (NO_ERR);
}

t_err	parse_cylinder(char **split, t_scene *scene)
{
	(void)scene;
	(void)split;
	printf("[parse_cylinder]\n");
	return (NO_ERR);
}

t_err	parse_type(char **split, t_scene *scene)
{
//	printf("parsing line: %s$\n", line);
	if (ft_strncmp(split[0], "A", 2) == 0)
		return (parse_ambient(split, &scene->ambient_light));
	else if (ft_strncmp(split[0], "C", 2) == 0)
		return (parse_camera(split, &scene->cameras));
	else if (ft_strncmp(split[0], "L", 2) == 0)
		return (parse_light(split, scene));
	else if (ft_strncmp(split[0], "R", 2) == 0)
		return (parse_resolution(split, scene));
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		return (parse_sphere(split, scene));
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		return (parse_plane(split, scene));
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		return (parse_cylinder(split, scene));
	else
		return (INVALID_OBJ);
	return (NO_ERR);
}

t_err	parse_line(char *line, t_scene *scene)
{
	t_err	err;
	char	**split;

	if (line[0] == '\n')
		return (EMPTY_LINE);
	split = ft_split_isspace(line);
	if (!split)
		return (EMPTY_LINE);
	if (split[0][0] == '#')
	{
		ft_free_split(&split);
		return (EMPTY_LINE);
	}

	err = parse_type(split, scene);
	ft_free_split(&split);
	return (err);
}

t_err	parse_file(const char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len < 4)
	{
		printf("[parse_file] filename invalid\n");
		return (PARSE_F);
	}
	if (ft_strncmp(".rt", arg + len - 3, 4) == 0)
		return (NO_ERR);
	printf("[parse_file] filename invalid (extension)\n");
	return (PARSE_F);
}

t_err	add_count(char **split, t_scene *scene)
{
//	printf("parsing line: %s$\n", line);
	if (ft_strncmp(split[0], "A", 2) == 0)
		scene->ambient_light.amount++;
	else if (ft_strncmp(split[0], "C", 2) == 0)
		scene->cameras.amount++;
	else if (ft_strncmp(split[0], "L", 2) == 0)
		scene->lights.amount++;
	else if (ft_strncmp(split[0], "R", 2) == 0)
		(void)scene->resolution_x; ///?!?! wat nu
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		scene->spheres.amount++;
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		scene->planes.amount++;
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		scene->cylinders.amount++;
	else
		return (INVALID_OBJ);
	return (NO_ERR);
}

t_err	parse_identifier(char *line, t_scene *scene)
{
	t_err	err;
	char	**split;

	if (line[0] == '\n')
		return (EMPTY_LINE);
	split = ft_split_isspace(line);
	if (!split)
		return (EMPTY_LINE);
	if (split[0][0] == '#')
	{
		ft_free_split(&split);
		return (EMPTY_LINE);
	}
	err = add_count(split, scene);
	ft_free_split(&split);
	return (err);
}

t_err	count_identifiers(char const *arg, t_scene *scene)
{
	t_err	err;
	int		fd;
	char	*line;

	fd = open(arg, O_RDONLY, 0644);
	if (fd < 0)
		return (printf("[parse_identifiers] error open fd = %d\n", fd));
	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		err = parse_identifier(line, scene);
		free(line);
		if (err != NO_ERR && err != EMPTY_LINE)
		{
			printf(RED "[parse_identifiers] parse error: %s\n" RESET, line);
			return (err);
		}
	}
	close(fd);
//	if (scene->ambient_light.amount > 1)
//	{
//		printf("[count_identifiers] to many ambient?\n");
//		return (PARSE_F);
//	}
	return (NO_ERR);
}

t_err	parse_identifiers(char const *arg, t_scene *scene)
{
	t_err	err;
	int 	fd;
	char	*line;

	err = parse_file(arg);
	if (err != NO_ERR)
		return (err);
	fd = open(arg, O_RDONLY, 0644);
	if (fd < 0)
		return (printf("error open, fd = %d\n", fd));
	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		err = parse_line(line, scene);
		free(line);
		if (err != NO_ERR && err != EMPTY_LINE)
		{
			printf(RED "parse error: %s\n" RESET, line);
			return (err);
		}
	}
	close(fd);
	return (NO_ERR);
}

t_err	alloc_object(t_rt_object *object)
{
	if (object->type == CAMERA)
		object->obj = ft_calloc(sizeof(t_rt_obj_camera), object->amount);
	else if (object->type == LIGHT_P)
		object->obj = ft_calloc(sizeof(t_rt_obj_light), object->amount);
	else if (object->type == PLANE)
		object->obj = ft_calloc(sizeof(t_rt_obj_plane), object->amount);
	else if (object->type == SPHERE)
		object->obj = ft_calloc(sizeof(t_rt_obj_sphere), object->amount);
	else if (object->type == CYLINDER)
		object->obj = ft_calloc(sizeof(t_rt_obj_cylinder), object->amount);
	if (!object->obj)
		return (MALLOC_F);
	return (NO_ERR);
}

t_err	alloc_scene(t_scene *scene)
{
	if (alloc_object(&scene->cameras) != NO_ERR)
		return (MALLOC_F);
	if (alloc_object(&scene->lights) != NO_ERR)
		return (MALLOC_F);
	if (alloc_object(&scene->planes) != NO_ERR)
		return (MALLOC_F);
	if (alloc_object(&scene->spheres) != NO_ERR)
		return (MALLOC_F);
	if (alloc_object(&scene->cylinders) != NO_ERR)
		return (MALLOC_F);
	return (NO_ERR);
}

t_err	parse_input(char const *arg, t_scene *scene)
{
	t_err	err;

	err = count_identifiers(arg, scene);
	if (err != NO_ERR)
		return (err);
	/// check min req
	err = alloc_scene(scene);
	if (err != NO_ERR)
		return (err);
	err = parse_identifiers(arg, scene);
	return (err);
}