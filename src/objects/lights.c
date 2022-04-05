#include <datatypes.h>
#include <libft.h>

t_rt_shape	new_ambient_light(double ratio, t_color color)
{
	t_rt_shape light;

	light.ratio = ratio;
	light.color = color;
	return (light);
}

t_rt_shape	*new_point_light(double ratio, t_position pos, t_color color)
{
	t_rt_shape *light;

	light = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (!light)
		return (light);
	light->ratio = ratio;
	light->color = color;
	light->pos1 = pos;
	return (light);
}