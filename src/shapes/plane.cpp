#include "plane.hpp"

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
bool intersects(shapes::plane shape, math::ray3d ray)
{
  const auto dir_norm_dot = math::dot(ray.direction, shape.normal);

  // Line parallel to the plane.
  // Ignore line contained on the plane to avoid self-intersection problems.
  if (dir_norm_dot == 0.0f) { return false; }

    const auto d = math::dot(math::make_vector3d(ray.origin, shape.center), shape.normal) / dir_norm_dot;

    // Intersection ahead of ray origin.
    return d > 0.0f;
}

// Returns the closest intersection point between ray and plane.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::plane shape, math::ray3d ray)
{
  const auto dir_norm_dot = math::dot(ray.direction, shape.normal);

  // Line parallel to the plane.
  // Ignore line contained on the plane to avoid self-intersection problems.
  if (dir_norm_dot == 0.0f) { return boost::none; }

  const auto d = math::dot(math::make_vector3d(ray.origin, shape.center), shape.normal) / dir_norm_dot;

  // Intersection before ray origin.
  if (d <= 0) { return boost::none; }

  shapes::intersection_info info;
  info.point = math::translated(ray.origin, math::scaled(ray.direction, d));
  info.normal = std::signbit(dir_norm_dot) ? shape.normal : -shape.normal;
  return info;
}

}
