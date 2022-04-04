#include <datatypes.h>
#include <intersect.h>
#include <vector_utils.h>
#include <math.h>

t_quad_result	intersect_sphere(t_vector o, t_vector d, t_rt_shape *shape)
{
	t_quad_abc		quad;
	t_quad_result	result;
	t_vector		co;
	double 			discriminant;

	co = substract_vector(o, shape->vector);
	quad.a = dot_product(d, d);
	quad.b = 2 * dot_product(co, d);
	quad.c = dot_product(co, co) - shape->radius * shape->radius;
	discriminant = quad.b * quad.b - 4 * quad.a * quad.c;
	if (discriminant < 0)
		return ((t_quad_result){INFINITY, INFINITY});
	result.t1 = (-1 * quad.b + sqrt(discriminant)) / (2 * quad.a);
	result.t2 = (-1 * quad.b - sqrt(discriminant)) / (2 * quad.a);
	return (result);
}

t_quad_result	intersect_shape(t_vector o, t_vector d, t_rt_shape *shape)
{
	static t_intersect	function_pointers[NO_OBJECT] = {
			[SPHERE] = intersect_sphere
	};
	return (function_pointers[shape->type](o, d, shape));
}
