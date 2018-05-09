#include "quadrilateral.hpp"

#include "intersection_info.hpp"
#include "triangle.hpp"

#include <math/point3d.hpp>
#include <math/ray3d.hpp>
#include <math/utility.hpp>
#include <math/vector3d.hpp>

#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <cmath>

namespace shapes
{

// Check for ray-plane intersection using geometric test.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
bool intersects(shapes::quadrilateral shape, math::ray3d ray)
{
	shapes::triangle t1{ shape.p1, shape.p2, shape.p3 };
	shapes::triangle t2{ shape.p3, shape.p4, shape.p1 };

	return intersects(t1, ray) || intersects(t2, ray);
}

// Returns the closest intersection point between ray and plane.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::quadrilateral shape, math::ray3d ray, bool backface = true)
{
	shapes::triangle t1{ shape.p1, shape.p2, shape.p3 };

	const auto inter = closest_intersection(t1, ray, backface);
	if (inter.is_initialized())
	{
		return inter;
	}

	shapes::triangle t2{ shape.p3, shape.p4, shape.p1 };
	return closest_intersection(t2, ray, backface);
}

}
