#ifndef LIGHTS_H
#define LIGHTS_H

t_rt_shape	new_ambient_light(double ratio, t_color color);
t_rt_shape	*new_point_light(double ratio, t_position pos, t_color color);

#endif
