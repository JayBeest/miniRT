#include <stddef.h>
#include <datatypes.h>
#include <draw_utils.h>
#include <vector_utils.h>
#include <intersect.h>
#include <math.h>

#include <stdio.h>
#include <libft.h>
#include <unistd.h>

t_vector	canvas_to_viewport(int x, int y, t_scene scene)
{
	t_vector	v;

	v.x = x * scene.viewport_x / scene.resolution_x;
	v.y = y * scene.viewport_y / scene.resolution_y;
	v.z = scene.d;
	return (v);
}



t_color	trace_ray(t_vector o, t_vector d, t_scene scene)
{
	t_rt_shape		*node;
	double			closest_t;
	t_rt_shape		*closest_sphere;
	t_quad_result	quad_result;

	closest_sphere = NULL;
	node = scene.shapes;
	closest_t = INFINITY;
	while (node)
	{
		quad_result = intersect_shape(o, d, node);
		if (quad_result.t1 > 1 && quad_result.t1 < 1000 && quad_result.t1 < closest_t)
		{
			closest_t = quad_result.t1;
			closest_sphere = node;
		}
		if (quad_result.t2 > 1 && quad_result.t2 < 1000 && quad_result.t2 < closest_t)
		{
			closest_t = quad_result.t2;
			closest_sphere = node;
		}
		node = node->next;
	}
	if (!closest_sphere)
		return ((t_color){0, 0, 0, 255});
	return (closest_sphere->color);
}

t_err	render_scene(t_minirt *rt)
{
	int			x;
	int			y;
	t_vector	d;
	t_color		color;
//	t_err	err;

//	init_scene(&rt); ???
	x = -1 * rt->scene.resolution_x / 2;
	while (x < rt->scene.resolution_x / 2)
	{
		y= -1 * rt->scene.resolution_y / 2;
		while (y < rt->scene.resolution_y / 2)
		{
			d = canvas_to_viewport(x, y, rt->scene);
			color = trace_ray(rt->scene.origin, d, rt->scene);
			rt_putpixel(x, y, color_to_int(color), rt);
			y++;
		}
		x++;
	}
//	char	*str = ft_calloc(20, 1);
//	sprintf(str, "d to c: %d", rt->scene.d);
//	mlx_delete_image(rt->mlx.mlx, rt->mlx.text);
//	rt->mlx.text = mlx_put_string(rt->mlx.mlx, str, 20, 20);
//	ft_free_str(&str);
//	usleep(500000);
	return (NO_ERR);
}