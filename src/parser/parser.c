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
	if (get_ratio(split[1], &ambient->ratio) != NO_ERR)
		return (PARSE_F);
	if (parse_rgb(split[2], &ambient->color) != NO_ERR)
	{
		printf("[parse_ambient] colour fail %s\n", split[2]);
		return (PARSE_F);
	}
	return (NO_ERR);
}

t_err	parse_camera(char **split, t_rt_object *object, int camera_id)
{
	t_err		err;
	static int	id;

	printf("[parse_camera]\n");
	err = get_xyz(split[1], &(((t_rt_obj_camera *)(object->obj))[id]).position);
	if (err != NO_ERR)
		return (err);
	err = get_xyz(split[2], &(((t_rt_obj_camera *)(object->obj))[id]).orientation);
	if (err != NO_ERR)
		return (err);
	err = get_fov(split[3], &(((t_rt_obj_camera *)(object->obj))[id]).fov);
	if (err != NO_ERR)
		return (err);
	(((t_rt_obj_camera *)(object->obj))[id]).id = camera_id;
	id++;
	return (err);
}

t_err	parse_light(char **split, t_rt_object *object, int light_id)
{
	t_err		err;
	static int	id;

	printf("[parse_light]\n");
	err = get_xyz(split[1], &(((t_rt_obj_light *)(object->obj))[id]).position);
	if (err != NO_ERR)
		return (err);
	err = get_ratio(split[2], &(((t_rt_obj_light *)(object->obj))[id]).ratio);
	if (err != NO_ERR)
		return (err);
	err = parse_rgb(split[3], &(((t_rt_obj_light *)(object->obj))[id]).color);
	if (err != NO_ERR)
		return (err);
	(((t_rt_obj_light *)(object->obj))[id]).id = light_id;
	id++;
	return (err);
}

t_err	parse_resolution(char **split, t_scene *scene)
{
	t_err	err;

	printf("[parse_resolution]\n");
	err = get_resolution(split[1], &scene->resolution_x);
	if (err != NO_ERR)
		return (err);
	return (get_resolution(split[2], &scene->resolution_y));
}

t_err	parse_sphere(char **split, t_rt_object *object, int id)
{
	t_err		err;

	printf("[parse_sphere]\n");
	err = get_xyz(split[1], &(((t_rt_obj_shape *)(object->obj))[id]).position);
	if (err != NO_ERR)
		return (err);
	err = get_radius(split[2], &(((t_rt_obj_shape *)(object->obj))[id]).radius);
	if (err != NO_ERR)
		return (err);
	err = parse_rgb(split[3], &(((t_rt_obj_shape *)(object->obj))[id]).color);
	if (err != NO_ERR)
		return (err);
	(((t_rt_obj_shape *)(object->obj))[id]).id = id;
	return (err);
}

t_err	parse_plane(char **split, t_rt_object *object, int id)
{
	t_err		err;

	printf("[parse_plane]\n");
	err = get_xyz(split[1], &(((t_rt_obj_shape *)(object->obj))[id]).position);
	if (err != NO_ERR)
		return (err);
	err = get_xyz(split[2], &(((t_rt_obj_shape *)(object->obj))[id]).orientation);
	if (err != NO_ERR)
		return (err);
	err = parse_rgb(split[3], &(((t_rt_obj_shape *)(object->obj))[id]).color);
	if (err != NO_ERR)
		return (err);
	(((t_rt_obj_shape *)(object->obj))[id]).id = id;
	return (err);
}

t_err	parse_cylinder(char **split, t_rt_object *object, int id)
{
	t_err		err;

	printf("[parse_cylinder]\n");
	err = get_xyz(split[1], &(((t_rt_obj_shape *)(object->obj))[id]).position);
	if (err != NO_ERR)
		return (err);
	err = get_xyz(split[2], &(((t_rt_obj_shape *)(object->obj))[id]).orientation);
	if (err != NO_ERR)
		return (err);
	err = get_pos(split[3], &(((t_rt_obj_shape *)(object->obj))[id]).radius);
	if (err != NO_ERR)
		return (err);
	(((t_rt_obj_shape *)(object->obj))[id]).radius /= 2;
	err = get_pos(split[4], &(((t_rt_obj_shape *)(object->obj))[id]).height);
	if (err != NO_ERR)
		return (err);
	err = parse_rgb(split[5], &(((t_rt_obj_shape *)(object->obj))[id]).color);
	if (err != NO_ERR)
		return (err);
	(((t_rt_obj_shape *)(object->obj))[id]).id = id;
	return (err);
}

t_err	parse_type(char **split, t_scene *scene)
{
	static int	shape_id;
	static int	light_id;
	static int	camera_id;

	if (ft_strncmp(split[0], "A", 2) == 0)
		return (parse_ambient(split, &scene->ambient_light));
	else if (ft_strncmp(split[0], "C", 2) == 0)
		return (parse_camera(split, &scene->cameras, camera_id++));
	else if (ft_strncmp(split[0], "L", 2) == 0)
		return (parse_light(split, &scene->lights, light_id++));
	else if (ft_strncmp(split[0], "R", 2) == 0)
		return (parse_resolution(split, scene));
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		return (parse_sphere(split, &scene->shapes, shape_id++));
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		return (parse_plane(split, &scene->shapes, shape_id++));
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		return (parse_cylinder(split, &scene->shapes, shape_id++));
	else
		return (INVALID_OBJ);
}

t_err	parse_line(char *line, t_scene *scene)
{
	t_err	err;
	char	**split;

	if (line[0] == '\n')
		return (EMPTY_LINE);
	split = ft_split(line, ' ');
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
		scene->shapes.amount++;
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		scene->shapes.amount++;
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		scene->shapes.amount++;
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
	split = ft_split(line, ' ');
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
			close(fd);
			printf(RED "[parse_identifiers] parse error: %s\n" RESET, line);
			return (err);
		}
	}
	close(fd);
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

t_err	alloc_scene(t_scene *scene)
{
	scene->cameras.obj = ft_calloc(sizeof(t_rt_obj_camera), scene->cameras.amount);
	if (!scene->cameras.obj)
		return (MALLOC_F);
	scene->lights.obj = ft_calloc(sizeof(t_rt_obj_light), scene->lights.amount);
	if (!scene->lights.obj)
		return (MALLOC_F);
	scene->shapes.obj = ft_calloc(sizeof (t_rt_obj_shape), scene->shapes.amount);
	if (!scene->shapes.obj)
		return (MALLOC_F);
	return (NO_ERR);
}

void	print_stuff(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->cameras.amount)
	{
		printf("Camera id %d\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).id);
		printf("	x %f\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).position.x);
		printf("	y %f\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).position.y);
		printf("	z %f\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).position.z);
		printf("	x %f\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).orientation.x);
		printf("	y %f\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).orientation.y);
		printf("	z %f\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).orientation.z);
		printf("	fov %d\n", (((t_rt_obj_camera *)(scene->cameras.obj))[i]).fov);
		i++;
	}
	i = 0;
	while (i < scene->lights.amount)
	{
		printf("Light id %d\n", (((t_rt_obj_light *)(scene->lights.obj))[i]).id);
		printf("	x %f\n", (((t_rt_obj_light *)(scene->lights.obj))[i]).position.x);
		printf("	y %f\n", (((t_rt_obj_light *)(scene->lights.obj))[i]).position.y);
		printf("	z %f\n", (((t_rt_obj_light *)(scene->lights.obj))[i]).position.z);
		printf("	brightness %f\n", (((t_rt_obj_light *)(scene->lights.obj))[i]).ratio);
		printf("	rgb %d,%d,%d\n", (((t_rt_obj_light *)(scene->lights.obj))[i]).color.r, (((t_rt_obj_light *)(scene->lights.obj))[i]).color.g, (((t_rt_obj_light *)(scene->lights.obj))[i]).color.b);
		i++;
	}
	i = 0;
	while (i < scene->shapes.amount)
	{
		printf("Shape id %d\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).id);
		printf("	x %f\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).position.x);
		printf("	y %f\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).position.y);
		printf("	z %f\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).position.z);
		printf("	x %f\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).orientation.x);
		printf("	y %f\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).orientation.y);
		printf("	z %f\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).orientation.z);
		printf("	rgb %d,%d,%d\n", (((t_rt_obj_shape *)(scene->shapes.obj))[i]).color.r, (((t_rt_obj_shape *)(scene->shapes.obj))[i]).color.g, (((t_rt_obj_shape *)(scene->shapes.obj))[i]).color.b);
		i++;
	}
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
	print_stuff(scene);
	return (err);
}