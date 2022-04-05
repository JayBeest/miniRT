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

t_color	multip_color(double intensity, t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r * intensity;
	g = color.g * intensity;
	b = color.b * intensity;
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	calculate_light(t_rt_shape *shape, t_vector n, t_vector p, t_scene scene)
{
	double		intensity;
	int			i;
	t_vector	l;
	double		n_dot_l;

	i = 0;
	intensity = scene.ambient_ligth.ratio;
	while (scene.lights)
	{
		l = substract_vector(scene.lights->vector, p);
		scene.lights = scene.lights->next;
		n_dot_l = dot_product(n, l);
		if (n_dot_l > 0)
			intensity += scene.lights->ratio * n_dot_l / (sqrt(dot_product(n, n)) * sqrt(dot_product(l, l)));
		scene.lights = scene.lights->next;
	}
	return (multip_color(intensity, shape->color));
}

t_color	precalculate_light(t_rt_shape *shape, t_vector o, t_vector d, double closest_t, t_scene scene)
{
	t_vector	p;
	t_vector	n;

	p = multip_vector(d, closest_t);
	p = add_vector(p, o);
	n = substract_vector(p, shape->vector);
	n = multip_vector(n, (double)1 / sqrt(dot_product(n, n)));
	return (calculate_light(shape, p, n, scene));
}

t_color	trace_ray(t_vector o, t_vector d, t_scene scene)
{
	t_rt_shape		*node;
	double			closest_t;
	t_rt_shape		*closest_sphere;
	t_quad_result	quad_result;

	int				edge;
	int				d_edge;

	closest_sphere = NULL;
	node = scene.shapes;
	closest_t = INFINITY;
	while (node)
	{
		edge = 0;
		d_edge = 0;
		quad_result = intersect_shape(o, d, node);
		if (quad_result.t1 < 1000 && quad_result.t1 > 1 && quad_result.t1 == quad_result.t2)
		{
			printf(RED "edge found!!\n" RESET);
			closest_t = quad_result.t1;
			closest_sphere = node;
			edge = 1;
		}
		else
		{
			if (quad_result.t1 > 1 && quad_result.t1 < 1000 && quad_result.t1 < closest_t)
			{
				closest_t = quad_result.t1;
				closest_sphere = node;
				edge = 0;
			}
			if (quad_result.t2 > 1 && quad_result.t2 < 1000 && quad_result.t2 < closest_t)
			{
				closest_t = quad_result.t2;
				closest_sphere = node;
				edge = 0;
			}
		}
		node = node->next;
	}
	if (!closest_sphere)
		return ((t_color){0, 0, 0, 255});
	if (edge)
		return ((t_color){0, 255, 204, 255});
	return (precalculate_light(closest_sphere, o, d, closest_t, scene));
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