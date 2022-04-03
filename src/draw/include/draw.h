#ifndef DRAW_H
# define DRAW_H

int		color_to_int(t_color color);
t_err	rt_putpixel(int x, int y, int color, t_minirt *rt);
t_err	render_scene(t_minirt *rt);

#endif