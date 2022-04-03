#include <libft.h>
#include <datatypes.h>

t_rt_shape *new_sphere(int radius, t_vector pos, t_color color)
{
	t_rt_shape *obj;

	obj = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (!obj)
		return (obj);
	obj->type = SPHERE;
	obj->radius = radius;
	obj->vector = pos;
	obj->color = color;
	return (obj);
}