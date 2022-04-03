#include <libft.h>
#include <datatypes.h>

t_rt_shape *new_rt_object(t_rt_shape_type type)
{
	t_rt_shape *obj;

	obj = (t_rt_shape *)ft_calloc(sizeof(t_rt_shape), 1);
	if (obj)
		obj->type = type;
	return (obj);
}