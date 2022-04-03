#ifndef INTERSECT_H
# define INTERSECT_H

typedef t_quad_result(*t_intersect)(t_vector, t_vector, t_rt_shape*);

t_quad_result	intersect_shape(t_vector origin, t_vector viewport, t_rt_shape *shape);

#endif
