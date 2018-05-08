#include "triangle.hpp"

#include "intersection_info.hpp"

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
bool intersects(shapes::triangle shape, math::ray3d ray)
{
	const auto e1 = math::make_vector3d(shape.p1, shape.p2);
	const auto e2 = math::make_vector3d(shape.p1, shape.p3);
	const auto s1 = math::cross(ray.direction, e2);
	const auto divisor = math::dot(s1, e1);

	if (divisor == 0.0f) { return false; }

	const auto inv_divisor = 1.0f / divisor;

	const auto s = math::make_vector3d(shape.p1, ray.origin);
	const auto b1 = math::dot(s, s1) * inv_divisor;
	if (b1 < 0.0f || b1 > 1.0f) { return false; }

	const auto s2 = math::cross(s, e1);
	const auto b2 = math::dot(ray.direction, s2) * inv_divisor;
	if (b2 < 0.0f || b2 + b1 > 1.0f) { return false; }

	const auto d = math::dot(e2, s2) * inv_divisor;
	return d > 0.0f;
}

// Returns the closest intersection point between ray and plane.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::triangle shape, math::ray3d ray)
{
	const auto e1 = math::make_vector3d(shape.p1, shape.p2);
	const auto e2 = math::make_vector3d(shape.p1, shape.p3);
	const auto s1 = math::cross(ray.direction, e2);
	const auto divisor = math::dot(s1, e1);

	if (divisor == 0.0f) { return boost::none; }

	const auto inv_divisor = 1.0f / divisor;

	const auto s = math::make_vector3d(shape.p1, ray.origin);
	const auto b1 = math::dot(s, s1) * inv_divisor;
	if (b1 < 0.0f || b1 > 1.0f) { return boost::none; }

	const auto s2 = math::cross(s, e1);
	const auto b2 = math::dot(ray.direction, s2) * inv_divisor;
	if (b2 < 0.0f || b2 + b1 > 1.0f) { return boost::none; }

	const auto d = math::dot(e2, s2) * inv_divisor;
	if (d < 0.0f) { return boost::none; }

	const auto normal = math::normalized(math::cross(e2, e1));
	const auto dir_norm_dot = math::dot(ray.direction, normal);

  shapes::intersection_info info;
  info.point = math::translated(ray.origin, math::scaled(ray.direction, d));
  info.normal = std::signbit(dir_norm_dot) ? normal : -normal;
  return info;
}

}
