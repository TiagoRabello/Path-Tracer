#include "sphere.hpp"

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

// Check for ray-sphere intersection using geometric test.
//
// Note:
//  If ray origin is on the surface of the sphere and ray direction points
//  to the outside, no intersection is found.
bool intersects(shapes::sphere sphere, math::ray3d ray)
{
  const auto L = math::make_vector3d(ray.origin, sphere.center);
  const auto tPX = math::dot(L, ray.direction);

  const auto orig_center_sqrd_dist = math::squared_length(L);
  const auto squared_radius = sphere.radius * sphere.radius;

  // Ray origin is inside sphere.
  if (orig_center_sqrd_dist < squared_radius) { return true; }

  // Sphere center is behind ray origin.
  if (tPX <= 0.0f) { return false; }

  auto dsq = orig_center_sqrd_dist - tPX * tPX;
  return dsq <= squared_radius;
}

// Returns the closest intersection point between ray and sphere.
//
// Note:
//  If ray origin is on the surface of the sphere and ray direction points
//  to the outside, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::sphere sphere, math::ray3d ray)
{
  const auto L = math::make_vector3d(ray.origin, sphere.center);
  const auto tPX = math::dot(L, ray.direction);

  const auto orig_center_sqrd_dist = math::squared_length(L);
  const auto squared_radius = sphere.radius * sphere.radius;
  const auto origin_inside_sphere = orig_center_sqrd_dist < squared_radius;

  // Sphere center is behind ray origin.
  if (tPX <= 0.0f && origin_inside_sphere == false) { return boost::none; }

  const auto dsq = orig_center_sqrd_dist - tPX * tPX;
  if (dsq > squared_radius) { return boost::none; }

  float t;
  if (tPX > 0.0f && origin_inside_sphere == false)
  {
    t = tPX - std::sqrt(squared_radius - dsq);
  }
  else
  {
    t = tPX + std::sqrt(squared_radius - dsq);
  }

  shapes::intersection_info info;
  info.point = math::translated(ray.origin, math::scaled(ray.direction, t));
  info.normal = math::normalized(math::make_vector3d(sphere.center, info.point));
  return info;
}

}
